#include <cstdlib>
#include <iostream>
#include <chrono>

#include "philosopher.h"
#include "table.h"

void philosopher::function()
{
	while( tab->satisfied < tab->philosophers_cnt )
	{
		tranquil();
		thirsty();
		drinking();
	}
}

void philosopher::thirsty()
{
	lock->lock();

		int left_need = 0, right_need = 0;
		while(left_need + right_need == 0)
		{
			left_need = rand() % (tab->bottles_cnt + 1);
			right_need = rand() % (tab->bottles_cnt + 1);
		}

		std::cout << "Philosopher nr [" << id << "] needs " << left_need << " bottles on his left side and " << right_need << " bottles on his right side\n";

		if( *left_bottles >= left_need ){
			*left_bottles -= left_need;
			left_taken = left_need;
			left_need = 0;
		}

		else {
			left_taken = *left_bottles;
			*left_bottles = 0;
			left_need -= left_taken;
		}

		std::cout << "Philosopher nr [" << id << "] took " << left_taken << " bottles from his left side\n";

		if( *right_bottles >= right_need ){
			*right_bottles -= right_need;
			right_taken = right_need;
			right_need = 0;
		}
		else {
			right_taken = *right_bottles;
			*right_bottles = 0;
			right_need -= right_taken;
		}

		std::cout << "Philosopher nr [" << id << "] took " << right_taken << " bottles from his right side\n";

		if( left_need > 0 )
		{
			left_neighbour->send_message( message(true,true,left_need) );
			std::cout << "Philosopher nr [" << id << "] sent message to his left neighbour with request for " << left_need << " bottles\n";
		}

		if( right_need > 0 )
		{
			right_neighbour->send_message( message(false,true,right_need) );
			std::cout << "Philosopher nr [" << id << "] sent message to his right neighbour with request for " << right_need << " bottles\n";
		}

	lock->unlock();


	bool left_no_comeback = 0;
	bool right_no_comeback = 0;
	message left_message,right_message;

	while( left_need + right_need != 0 )
	{
		if( !mine->isEmpty() ) {

			lock->lock();

				message m = mine->receive_message();
				if( !m.request ){
					if( !m.neighbour ){
						left_taken += m.nr;
						left_need -= m.nr;
						std::cout << "Philosopher nr [" << id << "] received " << m.nr << " bottles from his left neighbour\n";
					}
					else {
						right_taken += m.nr;
						right_need -= m.nr;
						std::cout << "Philosopher nr [" << id << "] received " << m.nr << " bottles from his right neighbour\n";
					}
				}
				else{
					if( !m.neighbour ){
						if( m.no_return ){
							left_no_comeback = 1;
							left_message = m;
						}
						else {
							left_taken -= m.nr;
							left_need += m.nr;
							left_neighbour->send_message(message(true,false,m.nr));
							std::cout << "Philosopher nr [" << id << "] sent " << m.nr << " bottles to his left neighbour\n";
							left_neighbour->send_message(message(true,true,true,m.nr));
							std::cout << "Philosopher nr [" << id << "] sent message to his left neighbour with request for " << m.nr << " bottles\n";
						}
					}
					else {
						if( m.no_return ){
							right_no_comeback = 1;
							right_message = m;
						}
						else {
							right_taken -= m.nr;
							right_need += m.nr;
							right_neighbour->send_message(message(false,false,m.nr));
							std::cout << "Philosopher nr [" << id << "] sent " << m.nr << " bottles to his right neighbour\n";
							right_neighbour->send_message(message(false,true,true,m.nr));
							std::cout << "Philosopher nr [" << id << "] sent message to his right neighbour with request for " << m.nr << " bottles\n";
						}
					}
				}

			lock->unlock();
		}
	}

	if(left_no_comeback) mine->send_message(left_message);
	if(right_no_comeback) mine->send_message(right_message);
}

void philosopher::tranquil()
{
	int r = (rand() % 900) + 100;

	lock->lock();
		std::cout << "Philosopher nr [" << id << "] goes to sleep\n";
	lock->unlock();

	//BEGIN SLEEPING
	std::this_thread::sleep_for (std::chrono::milliseconds(r));
	//END SLEEPING

	lock->lock();
		std::cout << "Philosopher nr [" << id << "] wakes up from sleep\n";
	lock->unlock();
}

void philosopher::drinking()
{
	if( ++drink_cnt == tab->min_sessions ) ++tab->satisfied;


	int r = (rand() % 900) + 100;

	lock->lock();
		std::cout << "Philosopher nr [" << id << "] starts drinking\n";
	lock->unlock();

	//BEGIN DRINKING
	std::this_thread::sleep_for (std::chrono::milliseconds(r));
	//END DRINKING

	lock->lock();

		std::cout << "Philosopher nr [" << id << "] ends his " << drink_cnt << " drinking session\n";

		while( !mine->isEmpty() )
		{
			message m = mine->receive_message();
			if( !m.neighbour ){
				left_taken -= m.nr;
				left_neighbour->send_message(message(true,false,m.nr));
				std::cout << "Philosopher nr [" << id << "] sent " << m.nr << " bottles to his left neighbour\n";
			}
			else {
				right_taken -= m.nr;
				right_neighbour->send_message(message(false,false,m.nr));
				std::cout << "Philosopher nr [" << id << "] sent " << m.nr << " bottles to his right neighbour\n";
			}
		}

		*left_bottles += left_taken;
		std::cout << "Philosopher nr [" << id << "] put back " <<  left_taken << " bottles to his left side\n";
		left_taken = 0;

		*right_bottles += right_taken;
		std::cout << "Philosopher nr [" << id << "] put back " <<  right_taken << " bottles to his right side\n";
		right_taken = 0;

	lock->unlock();

}


philosopher::philosopher(table* tab, int id)
{
	this->id = id;
	this->tab = tab;
	mine = tab->mailboxes[id];
	right_neighbour = tab->mailboxes[ (id+1) % tab->philosophers_cnt ];
	left_neighbour = tab->mailboxes[ (id-1+tab->philosophers_cnt) % tab->philosophers_cnt ];
	right_bottles = &tab->bottles[ id ];
	left_bottles = &tab->bottles[ (id-1+tab->philosophers_cnt) % tab->philosophers_cnt ];	
	lock = &tab->lock;
}