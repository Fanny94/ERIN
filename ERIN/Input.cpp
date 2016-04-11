#include "Input.h"



Input::Input(GamePadIndex player)
{
	playerIndex = player;
	State.reset();
}


Input::~Input()
{
}

bool Input::isConnected()
{
	// clean the state
	memset(&controllerState, 0, sizeof(XINPUT_STATE));

	// Get the state
	DWORD Result = XInputGetState(0, &controllerState); // controllerNum = 0

	if (Result == ERROR_SUCCESS) return true;
	else return false;

	return false;
}

void Input::vibrate(float leftmotor, float rightmotor)
{
	// Create a new Vibraton 
	XINPUT_VIBRATION Vibration;

	memset(&Vibration, 0, sizeof(XINPUT_VIBRATION));

	int leftVib = (int)(leftmotor*65535.0f);
	int rightVib = (int)(rightmotor*65535.0f);

	// Set the Vibration Values
	Vibration.wLeftMotorSpeed = leftVib;
	Vibration.wRightMotorSpeed = rightVib;
	// Vibrate the controller
	XInputSetState((int)0, &Vibration); // controllerNum = 0
}

void Input::update()
{
	State.reset();
	// The values of the Left and Right Triggers go from 0 to 255. We just convert them to 0.0f=>1.0f
	if (controllerState.Gamepad.bRightTrigger && controllerState.Gamepad.bRightTrigger < XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
	{
		State._right_trigger = controllerState.Gamepad.bRightTrigger / 255.0f;
	}

	if (controllerState.Gamepad.bLeftTrigger && controllerState.Gamepad.bLeftTrigger < XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
	{
		State._left_trigger = controllerState.Gamepad.bLeftTrigger / 255.0f;
	}

	// Get the Buttons
	if (controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_A) State._buttons[GamePad_Button_A] = true;
	if (controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_B) State._buttons[GamePad_Button_B] = true;
	if (controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_X) State._buttons[GamePad_Button_X] = true;
	if (controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_Y) State._buttons[GamePad_Button_Y] = true;
	if (controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) State._buttons[GamePad_Button_DPAD_DOWN] = true;
	
	// Check to make sure we are not moving during the dead zone
	// Let's check the Left DeadZone
	if ((controllerState.Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
		controllerState.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
		(controllerState.Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
			controllerState.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
	{
		controllerState.Gamepad.sThumbLX = 0;
		controllerState.Gamepad.sThumbLY = 0;
	}

	// Check left thumbStick

	float leftThumbY = controllerState.Gamepad.sThumbLY;
	if (leftThumbY)
	{
		State._left_thumbstick.y = leftThumbY;
	}
	float leftThumbX = controllerState.Gamepad.sThumbLX;
	if (leftThumbX)
	{
		State._left_thumbstick.x = leftThumbX;
	}

	// Check right thumbStick

	float leftThumbY = controllerState.Gamepad.sThumbLY;
	if (leftThumbY)
	{
		State._left_thumbstick.y = leftThumbY;
	}
	float leftThumbX = controllerState.Gamepad.sThumbLX;
	if (leftThumbX)
	{
		State._left_thumbstick.x = leftThumbX;
	}
}

/*
official flags according to msdn

XINPUT_GAMEPAD_DPAD_UP          0x00000001
XINPUT_GAMEPAD_DPAD_DOWN        0x00000002
XINPUT_GAMEPAD_DPAD_LEFT        0x00000004
XINPUT_GAMEPAD_DPAD_RIGHT       0x00000008
XINPUT_GAMEPAD_START            0x00000010
XINPUT_GAMEPAD_BACK             0x00000020
XINPUT_GAMEPAD_LEFT_THUMB       0x00000040
XINPUT_GAMEPAD_RIGHT_THUMB      0x00000080
XINPUT_GAMEPAD_LEFT_SHOULDER    0x0100
XINPUT_GAMEPAD_RIGHT_SHOULDER   0x0200
XINPUT_GAMEPAD_A                0x1000
XINPUT_GAMEPAD_B                0x2000
XINPUT_GAMEPAD_X                0x4000
XINPUT_GAMEPAD_Y                0x8000
*/