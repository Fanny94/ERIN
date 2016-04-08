#ifndef COMPONENT_H
#define COMPONENT_H
#include "GameObject.h"

enum ComponentType
{
	Comp_Controls,
	Comp_Physics,
	Comp_Transform,
};

class Component : public GameObject
{
public:
	Component();
	virtual ~Component();
private:
	ComponentType componentType;
};

#endif // !COMPONENT_H

