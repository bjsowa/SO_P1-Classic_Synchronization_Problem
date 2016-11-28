#include <thread>
#include <iostream>

#include "table.h"
#include "philosopher.h"

table::table(int ph, int bo, int s)
	: philosophers_cnt(ph),
	  bottles_cnt(bo),
	  min_sessions(s) {

	mailboxes = (mailbox**)malloc(philosophers_cnt * sizeof(mailbox*));
	for( int i = 0; i < philosophers_cnt; ++i )
		mailboxes[i] = new mailbox();

	bottles = (int*)malloc(philosophers_cnt * sizeof(int));
	for( int i = 0; i < philosophers_cnt; ++i )
		bottles[i] = bottles_cnt;

	philosophers = (philosopher**)malloc(philosophers_cnt * sizeof(philosopher*));
	for( int i = 0; i < philosophers_cnt; ++i )
		philosophers[i] = new philosopher(this,i);

	procs = (std::thread*)malloc(philosophers_cnt * sizeof(std::thread));
}

void table::run()
{
	for( int i = 0; i < philosophers_cnt; ++i )
		procs[i] = philosophers[i]->spawn();

	for( int i = 0; i < philosophers_cnt; ++i )
		procs[i].join();

	std::cout << "\nNumber of drinking sessions for each philosopher:\n";
	for( int i = 0; i < philosophers_cnt; ++i )
		std::cout << "[" << i << "] - " << philosophers[i]->drink_cnt << "\n";
}