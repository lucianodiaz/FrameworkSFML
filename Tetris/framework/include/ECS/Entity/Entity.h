#pragma once
#include <string>
#include <ECS/Component/CTransform.h>
#include <ECS/Component/CShape.h>
#include <ECS/Component/CDrawable.h>

using std::string;

template<typename ENTITY>
class Entity
{
protected:
	template<typename> friend class EntityManager;

	Entity(const string& tag, const size_t id) : _tag(tag), _id(id){}
	string _tag{ "default" };
	bool _alive = true;
	size_t _id = 0;
public:
	void destroy() { _alive = false; };
	bool isAlive()const { return _alive; }
	const string& tag()const { return _tag; }
	const size_t id()const { return _id; }
};

