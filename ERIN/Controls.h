#ifndef CONTROLS_H
#define CONTROLS_H
#include "Component.h"

enum ControlsType
{
	Con_Input,
	Con_Behavior,
};
class Controls : public Component
{
public:
	Controls();
	virtual ~Controls();

	virtual void update();
};

#endif // !CONTROLS_H

