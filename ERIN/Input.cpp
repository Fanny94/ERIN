#include "Input.h"



Input::Input()
{
}


Input::~Input()
{
	//delete pad;
}

bool Input::IsXBOXControlConnected()
{
	//Invoke the memset(); function to zero the XBOX_CONTROLLER_State. 
	//memset(&XBOX_CONTROLLER_State, 0, sizeof(XINPUT_STATE));

	//We store the XInputGetState value inside result, note that result is a DWORD which is a typedef unsigned long. 
	//DWORD result = XInputGetState(XBOX_CONTROLLER_NUM, &XBOX_CONTROLLER_State);

	//Check if the controller is disconnected using the Ternary Operator. 
	//return  result == ERROR_DEVICE_NOT_CONNECTED ? false : true;
	return false;
}

void Input::update()
{

}
