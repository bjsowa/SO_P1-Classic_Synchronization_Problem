#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#include <thread>
#include "mailbox.h"
#include "spinlock.h"

struct table;

class philosopher
{
	int id;
	table* tab;
	mailbox* left_neighbour;
	mailbox* right_neighbour;
	mailbox* mine;
	int* left_bottles;
	int* right_bottles;
	Spinlock* lock;

	int left_taken = 0, right_taken = 0;

public:
	int drink_cnt = 0;
	
	philosopher(table* t, int id);
	void function();
	void thirsty();
	void tranquil();
	void drinking();

	std::thread spawn() {
      	return std::thread( [this] { this->function(); } );
    }
};


#endif