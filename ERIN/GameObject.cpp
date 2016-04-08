#include "GameObject.h"



GameObject::GameObject()
{
}

GameObject::GameObject(string name, float x, float y, float z)
{
	this->name = name;
	this->x = x;
	this->y = y;
	this->z = z;
}


GameObject::~GameObject()
{
}
