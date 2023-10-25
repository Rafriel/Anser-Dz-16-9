#include "Chat.h"
#include "Bad_Login.h"
#include <iostream>
//#include <map>
#include <set>

Chat::Chat() 
{
	_mess_count = 0;
	std::shared_ptr <User> newUser = std::make_shared <User>("All", "All", "\0");
	users_.emplace(make_pair("All", newUser));
}

Chat::~Chat() = default;

void Chat::setCurrentUser(const std::shared_ptr<User>& user) 
{

	if (user != nullptr)
		std::cout << std::endl << "Hello, " << user->getName() << std::endl;
	currentUser_ = user;
}

void Chat::login(const std::string& login, const std::string& password) 
{

	bool found = loginExist(login);
	if (!found)
		throw BadLogin();

	std::map<std::string, std::shared_ptr <User>>::iterator it = users_.find(login);
	if (it == users_.end())                                                      
		return;

	if (it->second->getPassword() == password) 
	{
		setCurrentUser(it->second);
	}
	else
		throw BadPassword();
}

void Chat::write(const std::string& text, std::shared_ptr<User> to) 
{

	std::shared_ptr <Message> _mess = std::make_shared<Message>(text, getCurrentUser()->getLogin(),
		to->getLogin());

	messages_.emplace(make_pair(_mess_count, _mess));
	getCurrentUser()->getMessage().insert(_mess_count);
	to->getMessage().insert(_mess_count);

	_mess_count++;
}

void Chat::writeAll(const std::string& text) 
{

	std::shared_ptr <Message> _mess = std::make_shared<Message>(text, getCurrentUser()->getLogin(), "All");
	messages_.emplace(make_pair(_mess_count, _mess));
	getCurrentUser()->getMessage().insert(_mess_count);
	_mess_count++;

	for (auto& to : users_)
	{
		if (to.second->getLogin() != getCurrentUser()->getLogin())
		{
			std::shared_ptr <Message> _mess = std::make_shared<Message>(text, getCurrentUser()->getLogin(),
				to.second->getLogin());
			messages_.emplace(make_pair(_mess_count, _mess));
			to.second->getMessage().insert(_mess_count);
			_mess_count++;
		}
	}
}

bool Chat::loginExist(const std::string& login) 
{
	std::map<std::string, std::shared_ptr <User>>::iterator it = users_.find(login);
	{
		if (it != users_.end())
			return true;
	}
	return false;
}

std::shared_ptr<User> Chat::getCurrentUser() 
{
	return currentUser_;
}

std::shared_ptr<User> Chat::getUserLogin(const std::string& login)
{
	for (auto& user : users_)
		if (user.second->getLogin() == login)
			return user.second;

	return std::make_shared <User>();
}

void Chat::showAllUserMesseges(std::shared_ptr<User> nummess) 
{

	if (nummess->getLogin() == "\0")
	{
		return;
	}

	std::cout << nummess->getName() << ", all your messages: " << std::endl << std::endl;

	for (const auto& i : nummess->getMessage()) 
	{

		std::map<int, std::shared_ptr <Message>>::iterator it = messages_.find(i);
		if (it == messages_.end())
			continue;
		std::shared_ptr <Message> message = it->second;

		std::cout << " from " << getUsers(message->getFrom()) << " to " << getUsers(message->getTo()) << ": " << "\" " << message->getText() << " \""
			<< std::endl << std::endl;
	}

}

std::ostream& operator<< (std::ostream& os, Chat& ch) 
{

	int count(0);
	for (auto& user : ch.users_)
	{
		os << " < " << user.second->getName() << " > ";
		count++;
		if (!(count % 6))
			os << std::endl;
	}
	return os;
}

bool Chat::userName(const std::string& name) 
{

	int count(0);

	for (auto& user : users_)
	{
		if (user.second->getName() == name)
			count++;
	}

	if (count == 1)
		return true;

	else
		return false;

}

const std::string Chat::getUsers(const std::string& login) 
{

	for (auto& user : users_)
	{

		if (user.second->getLogin() == login)
			return user.second->getName();

	}
	return "\0";

}

const std::string Chat::getUserName(const std::string& name) 
{

	for (auto& user : users_)
	{
		if (user.second->getName() == name)
			return user.second->getLogin();
	}
	return "\0";
}

void Chat::showAllUsers() const 
{
	for (auto& user : users_)
	{
		std::cout << user.second->getName() << " " << std::endl;
	}
}

void Chat::start()
{
	chatStart_ = true;
}

void Chat::mainMenu()
{
	currentUser_ = nullptr;

	std::string operation;
	do
	{
		std::cout << std::endl << "Login - 1  Registration - 2  Quit - 3" << std::endl;
		std::cout << std::endl << ">> ";
		std::cin >> operation;

		while (operation.size() > 1)                             
		{
			std::cout << std::endl << "1 or 2 or 3" << std::endl;
			std::cout << std::endl << ">> ";
			std::cin >> operation;
		}

		switch (operation.at(0))
		{
		case '1':
			loginUp();
			break;
		case '2':
			try
			{
				signUp();
			}
			catch (const std::exception& e)
			{
				std::cout << e.what() << std::endl;
			}
			break;
		case '3':
			chatStart_ = false;
			break;
		default:
			std::cout << "1 or 2 or 3" << std::endl;
			break;

		}


	} while (!currentUser_ && chatStart_);
}

void Chat::loginUp()
{
	std::string login, password;
	char operation;

	do
	{
		std::cout << std::endl << "login: ";
		std::cin >> login;
		std::cout << "password: ";
		std::cin >> password;

		try
		{
			Chat::login(login, password);
		}
		catch (BadLogin& e)
		{
			std::cout << e.what() << std::endl;
			break;
		}
		catch (BadPassword& e)
		{
			std::cout << e.what() << std::endl;
		}

	} while (!currentUser_);
}

void Chat::signUp()
{
	std::string login, password, name;

	std::cout << std::endl << "Enter login: ";
	std::cin >> login;

	if (loginExist(login) || login == "All")
	{
		throw Bad_Login();
	}

	std::cout << "Enter password: ";
	std::cin >> password;
	std::cout << "Enter name: ";
	std::cin >> name;

	std::shared_ptr <User> user = std::make_shared <User>(name, login, password);
	users_.emplace(make_pair(login, user));
	currentUser_ = user;
}

void Chat::userMenu()
{
	std::string operation;

	while (currentUser_)
	{
		std::cout << std::endl << "Show chat - 1  Add message - 2  Users - 3  Exit - 4" << std::endl;
		std::cout << std::endl << ">> ";
		std::cin >> operation;

		while (operation.size() > 1)                               
		{
			std::cout << std::endl << "unknown choise.." << std::endl;
			std::cout << std::endl << ">> ";
			std::cin >> operation;
		}

		switch (operation.at(0))
		{
		case '1':
			showAllUserMesseges(getCurrentUser());
			break;
		case '2':
			addMessage();
			break;
		case '3':
			showAllUsers();
			break;
		case '4':
			currentUser_ = nullptr;
			break;
		default:
			std::cout << std::endl << "unknown choise.." << std::endl;
			break;

		}

	}
}

void Chat::addMessage()
{
	std::string message;
	std::string name_to;
	std::string log_to;

	std::cout << std::endl << "select a user: \n";
	std::cout << *this << std::endl << std::endl;
	std::cin.ignore();
	std::getline(std::cin, name_to);

	while (!userName(name_to)) // ошибка выбора получателя
	{
		std::cout << std::endl << "Error: select a username from the list: \n";
		std::cout << *this << std::endl << std::endl;
		std::cout << std::endl;
		std::getline(std::cin, name_to);
	}

	log_to = getUserName(name_to);

	std::cout << std::endl << "Write the text of the message\n";
	std::cout << std::endl;
	std::getline(std::cin, message);
	std::cout << std::endl;
	if (getUserName(name_to) == "All")
	{
		writeAll(message);
	}
	else
		write(message, getUserLogin(log_to));
	
	std::cout << "Message from " << getCurrentUser()->getName() << " to " << getUsers(log_to) << " has been sent!" << std::endl << std::endl;
}