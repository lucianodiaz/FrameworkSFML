#pragma once
#include <string>

class Entity
{
	std::string _tag{"default"};
	bool _active;
	size_t _id;
	Entity(const std::string& tag, size_t id);
public:
	
	void destroy() { _active = false; };
	bool isActive()const { return _active; }
	const std::string& tag()const { return _tag; }
	size_t id()const { return _id; }
};