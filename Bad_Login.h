#pragma once
#include <exception>

class BadLogin : public std::exception
{
public:
	const char* what() const noexcept override
	{
		return "Error: invalid login!";
	}
};

class BadPassword : public std::exception
{
public:
	const char* what() const noexcept override
	{
		return "Error: invalid password!";
	}
};

class Bad_Login : public std::exception
{
public:
	const char* what() const noexcept override
	{
		return "Error: login is busy!";
	}
};

