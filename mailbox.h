#ifndef MAILBOX_H
#define MAILBOX_H

#include <queue>

struct message
{
	bool neighbour; //0 - left; 1 - right
	bool request; // 0 - bottle; 1 - request for bottle;
	bool no_return; // 0 - can return; 1 - cant
	int nr; //nr of bottles sended/needed

	message()
	{}

	message( bool n, bool r, int nr )
		: neighbour(n),
		  request(r),
		  no_return(false),
		  nr(nr) {}

	message( bool n, bool r, bool c, int nr )
		: neighbour(n),
		  request(r),
		  no_return(c),
		  nr(nr) {}
};

class mailbox
{
	std::queue<message> mails;

public:
	message receive_message();
	void send_message(message m);
	bool isEmpty() { return mails.empty(); }
};

#endif