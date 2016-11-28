#ifndef TABLE_H
#define TABLE_H

#include <cstdlib>
#include <thread>

#include "mailbox.h"
#include "spinlock.h"

class philosopher;

struct table
{
	int philosophers_cnt, bottles_cnt;
	mailbox** mailboxes;
	philosopher** philosophers;
	int* bottles;

	std::thread* procs;
	Spinlock lock;

	int min_sessions, satisfied = 0;

	table(int ph, int bo, int s);

	void run();
};

#endif