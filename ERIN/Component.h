#ifndef COMPONENT_H
#define COMPONENT_H

enum ComponentType
{
	Comp_Controls,
	Comp_Physics,
	Comp_Transform,
};

class Component
{
public:
	Component();
	~Component();

private:
	ComponentType componentType;
	Component* component;
};

#endif // !COMPONENT_H

