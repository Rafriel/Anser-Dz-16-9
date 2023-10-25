#include "Chat.h"
#include "Message.h"
#include "User.h"
#include "Bad_Login.h"
#include <iostream>


int main() 
{

	Chat chat;

	chat.start();

	while (chat.chatStart())
	{
		chat.mainMenu();
		while (chat.getCurrentUser())
		{
			chat.userMenu();
		}
	}

	return 0;
}
