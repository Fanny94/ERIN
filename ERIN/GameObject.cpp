#include "GameObject.h"



GameObject::GameObject()
	: name("noName"),
	x(0.0f), y(0.0f), z(0.0f)
{
}

GameObject::GameObject(string name, float x, float y, float z)
{
	this->name = name;
	this->x = x;
	this->y = y;
	this->z = z;

	this->input = new Input(GamePadIndex_One);
}


GameObject::~GameObject()
{
	
}
