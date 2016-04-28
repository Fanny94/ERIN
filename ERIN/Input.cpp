#include "Input.h"



Input::Input(GamePadIndex player)
{
	playerIndex = player;
	State.reset();

	deadzoneX = 0.05f;
	deadzoneY = 0.02f;
}


Input::~Input()
{
	if (isConnected()) vibrate(0.0f, 0.0f);
}


bool Input::isConnected()
{
	// clean the state
	memset(&_controllerState, 0, sizeof(XINPUT_STATE));

	// Get the state
	DWORD Result = XInputGetState(0, &_controllerState); // controllerNum = 0

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
	if (_controllerState.Gamepad.bRightTrigger && _controllerState.Gamepad.bRightTrigger < XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
	{
		State._right_trigger = _controllerState.Gamepad.bRightTrigger / 255.0f;
	}

	if (_controllerState.Gamepad.bLeftTrigger && _controllerState.Gamepad.bLeftTrigger < XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
	{
		State._left_trigger = _controllerState.Gamepad.bLeftTrigger / 255.0f;
	}

	// Get the Buttons
	if (_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) State._buttons[GamePad_Button_DPAD_UP] = true;
	if (_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) State._buttons[GamePad_Button_DPAD_DOWN] = true;
	if (_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) State._buttons[GamePad_Button_DPAD_LEFT] = true;
	if (_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) State._buttons[GamePad_Button_DPAD_RIGHT] = true;

	if (_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_START) State._buttons[GamePad_Button_START] = true;
	if (_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_BACK) State._buttons[GamePad_Button_BACK] = true;

	if (_controllerState.Gamepad.wButtons == XINPUT_GAMEPAD_LEFT_THUMB) State._buttons[GamePad_Button_LEFT_THUMB] = true;
	if (_controllerState.Gamepad.wButtons == XINPUT_GAMEPAD_RIGHT_THUMB) State._buttons[GamePad_Button_RIGHT_THUMB] = true;
	if (_controllerState.Gamepad.wButtons == XINPUT_GAMEPAD_LEFT_SHOULDER) State._buttons[GamePad_Button_LEFT_SHOULDER] = true;
	if (_controllerState.Gamepad.wButtons == XINPUT_GAMEPAD_RIGHT_SHOULDER) State._buttons[GamePad_Button_RIGHT_SHOULDER] = true;

	if (_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_A) State._buttons[GamePad_Button_A] = true;
	if (_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_B) State._buttons[GamePad_Button_B] = true;
	if (_controllerState.Gamepad.wButtons == XINPUT_GAMEPAD_X) State._buttons[GamePad_Button_X] = true;
	if (_controllerState.Gamepad.wButtons == XINPUT_GAMEPAD_Y) State._buttons[GamePad_Button_Y] = true;

	// Check to make sure we are not moving during the dead zone
	// Check the Left DeadZone

	if ((_controllerState.Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
		_controllerState.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
		(_controllerState.Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
			_controllerState.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
	{
		_controllerState.Gamepad.sThumbLX = 0;
		_controllerState.Gamepad.sThumbLY = 0;
	}
	
	// Check left thumbStick

	float leftThumbY = _controllerState.Gamepad.sThumbLY;

	if (leftThumbY)
	{
		leftThumbY = fmaxf(-1, leftThumbY / 32767);
		leftThumbY = (abs(leftThumbY) < deadzoneY ? 0 : (abs(leftThumbY) - deadzoneY) * (leftThumbY / abs(leftThumbY)));
		if (deadzoneY > 0) leftThumbY *= 1 / (1 - deadzoneY);
		State._left_thumbstick.y = leftThumbY;
	}

	float leftThumbX = _controllerState.Gamepad.sThumbLX;

	if (leftThumbX)
	{
		leftThumbX = fmaxf(-1, leftThumbX / 32767);
		leftThumbX = (abs(leftThumbX) < deadzoneX ? 0 : (abs(leftThumbX) - deadzoneX) * (leftThumbX / abs(leftThumbX)));
		if (deadzoneX > 0) leftThumbX *= 1 / (1 - deadzoneX);
		State._left_thumbstick.x = leftThumbX;
	}

	// Check the Right DeadZone

	if ((_controllerState.Gamepad.sThumbRX < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
		_controllerState.Gamepad.sThumbRX > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) &&
		(_controllerState.Gamepad.sThumbRY < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
			_controllerState.Gamepad.sThumbRY > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE))
	{
		_controllerState.Gamepad.sThumbRX = 0;
		_controllerState.Gamepad.sThumbRY = 0;
	}
	// Check right thumbStick

	float rightThumbY = _controllerState.Gamepad.sThumbRY;

	if (rightThumbY)
	{
		rightThumbY = fmaxf(-1, rightThumbY / 32767);
		rightThumbY = (abs(rightThumbY) < deadzoneY ? 0 : (abs(rightThumbY) - deadzoneY) * (rightThumbY / abs(rightThumbY)));
		if (deadzoneY > 0) rightThumbY *= 1 / (1 - deadzoneY);
		State._right_thumbstick.y = rightThumbY;
	}

	float rightThumbX = _controllerState.Gamepad.sThumbRX;

	if (rightThumbX)
	{
		rightThumbX = fmaxf(-1, rightThumbX / 32767);
		rightThumbX = (abs(rightThumbX) < deadzoneX ? 0 : (abs(rightThumbX) - deadzoneX) * (rightThumbX / abs(rightThumbX)));
		if (deadzoneX > 0) rightThumbX *= 1 / (1 - deadzoneX);
		State._right_thumbstick.x = rightThumbX;
	}
}