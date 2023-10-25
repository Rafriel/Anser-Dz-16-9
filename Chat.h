#pragma once
#include <string>
#include <memory>
#include <iostream>
#include "User.h"
#include "Message.h"
#include <map>
#include <set>

class Chat
{
private:

	std::map<std::string, std::shared_ptr <User>> users_;
	std::map<int, std::shared_ptr<Message>> messages_;
	std::shared_ptr <User> currentUser_ = nullptr;
	size_t _mess_count;

	bool chatStart_ = false;
	void loginUp();
	void signUp();
	void addMessage();

public:

	Chat();
	~Chat();

	std::size_t getMessCount() { return _mess_count; }
	void setCurrentUser(const std::shared_ptr<User>& user);
	void login(const std::string& login, const std::string& password);
	void write(const std::string& text, std::shared_ptr<User>);
	void writeAll(const std::string& text);
	bool loginExist(const std::string& login);
	void showAllUserMesseges(std::shared_ptr <User>);
	friend std::ostream& operator<< (std::ostream& os, Chat&);
	bool userName(const std::string& name);
	void showAllUsers() const;
	std::shared_ptr <User> getCurrentUser();
	std::shared_ptr <User> getUserLogin(const std::string& login);
	const std::string getUsers(const std::string& login);
	const std::string getUserName(const std::string& name);
	const std::map<std::string, std::shared_ptr <User>> getAllUsers() const { return users_; }
	const std::map<int, std::shared_ptr<Message>> getAllMessages() const { return messages_; }
	void mainMenu();
	void start();
	bool chatStart() const { return chatStart_; }
	void userMenu();

};

