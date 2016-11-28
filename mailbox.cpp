#include "mailbox.h"

message mailbox::receive_message()
{
	message m = mails.front();
	mails.pop();
	return m;
}

void mailbox::send_message(message m)
{
	mails.push(m);
}