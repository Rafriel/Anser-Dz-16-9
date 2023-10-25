#pragma once
#include <ostream>
#include <string>
#include <set>
class User
{
	std::string _name;
	const std::string _login;
	std::string _password;
	std::set<int> _mess; 
public:
	User() = default;
	User(const std::string& name, const std::string& login, const std::string& password) : _name(name), _login(login), _password(password) {}
	std::string& getName() { return _name; }
	const std::string& getLogin() { return _login; }
	std::string& getPassword() { return _password; }
	std::set<int>& getMessage() { return _mess; }



};