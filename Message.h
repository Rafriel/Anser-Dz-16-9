#pragma once
#include <string>

class Message
{
private:
	std::string _text;
	std::string _from;
	std::string _to;

public:
	Message(const std::string& text, const std::string& from, const std::string& to) : _text(text), _from(from), _to(to) {}

	const std::string getText()const { return _text; }
	const std::string& getFrom()const { return _from; }
	const std::string& getTo() const { return _to; }
};
