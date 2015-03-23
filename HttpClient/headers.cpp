#include "headers.h"
#include <istream>
#include <algorithm>
using namespace http;

Headers::Headers()
{
}

Headers::Headers(std::istream &in)
{
	//TODO
}

Headers::Headers(Headers &&o) : values_(std::move(o.values_))
{
}

Headers &Headers::operator=(Headers &&o)
{
	if (this != &o) {
		values_ = std::move(o.values_);
	}

	return *this;
}

void Headers::addValue(const std::string &field, const std::string &value)
{
	values_[field] = value;
}

void Headers::addValue(const std::string &field, int value)
{
	values_[field] = std::to_string(value);
}

bool Headers::hasValue(const std::string &field) const
{
	return (values_.find(field) != values_.end());
}

bool Headers::removeValue(const std::string &field)
{
	return (values_.erase(field) != 0);
}


std::string Headers::getString(const std::string &field, const std::string &defaultValue) const
{
	if (hasValue(field))
		return values_.at(field);
	else
		return defaultValue;
}

int Headers::getInt(const std::string &field, int defaultValue) const
{
	if (hasValue(field) && values_.at(field).find_first_not_of("0123456789") == std::string::npos)
		return std::stoi(values_.at(field));
	else
		return defaultValue;
}

std::string Headers::toString() const
{
	std::string str;
	for (const auto& p : values_)
		str += p.first + ": " + p.second + "\r\n";

	return str;
}