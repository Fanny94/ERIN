#ifndef INPUT_H
#define INPUT_H
#include "Controls.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <XInput.h>	// XInput API
#pragma comment(lib, "XInput.lib")

typedef enum
{
	GamePad_Button_DPAD_UP = 0,
	GamePad_Button_DPAD_DOWN = 1,
	GamePad_Button_DPAD_LEFT = 2,
	GamePad_Button_DPAD_RIGHT = 3,
	GamePad_Button_START = 4,
	GamePad_Button_BACK = 5,
	GamePad_Button_LEFT_THUMB = 6,
	GamePad_Button_RIGHT_THUMB = 7,
	GamePad_Button_LEFT_SHOULDER = 8,
	GamePad_Button_RIGHT_SHOULDER = 9,
	GamePad_Button_A = 10,
	GamePad_Button_B = 11,
	GamePad_Button_X = 12,
	GamePad_Button_Y = 13,
	GamePadButton_Max = 14
}GamePadButton;

typedef enum
{
	GamePadIndex_One = 0,
	GamePadIndex_Two = 1,
	GamePadIndex_Three = 2,
	GamePadIndex_Four = 3,
}GamePadIndex;

struct Vector2 // for the thumbsticks
{
	float x;
	float y;
};

struct GamePadState
{
	bool		_buttons[GamePadButton_Max];
	Vector2 	_left_thumbstick;
	Vector2	    _right_thumbstick;
	float		_left_trigger;
	float		_right_trigger;
	// Just to clear all values to default
	void reset()
	{
		for (int i = 0; i<(int)GamePadButton_Max; ++i) _buttons[i] = false;
		_left_thumbstick.x = 0.0f;
		_left_thumbstick.y = 0.0f;
		_right_thumbstick.x = 0.0f;
		_right_thumbstick.y = 0.0f;
		_left_trigger = _right_trigger = 0.0f;
	}
};
//
// Constants for gamepad buttons
//
#define XINPUT_GAMEPAD_DPAD_UP          0x0001
#define XINPUT_GAMEPAD_DPAD_DOWN        0x0002
#define XINPUT_GAMEPAD_DPAD_LEFT        0x0004
#define XINPUT_GAMEPAD_DPAD_RIGHT       0x0008
#define XINPUT_GAMEPAD_START            0x0010
#define XINPUT_GAMEPAD_BACK             0x0020
#define XINPUT_GAMEPAD_LEFT_THUMB       0x0040
#define XINPUT_GAMEPAD_RIGHT_THUMB      0x0080
#define XINPUT_GAMEPAD_LEFT_SHOULDER    0x0100
#define XINPUT_GAMEPAD_RIGHT_SHOULDER   0x0200
#define XINPUT_GAMEPAD_A                0x1000
#define XINPUT_GAMEPAD_B                0x2000
#define XINPUT_GAMEPAD_X                0x4000
#define XINPUT_GAMEPAD_Y                0x8000

class Input
{
public:
	Input(GamePadIndex player);
	~Input();

	bool isConnected();
	void vibrate(float leftmotor = 0.0f, float rightmotor = 0.0f);
	void update();

	GamePadState State;

private:
	XINPUT_STATE controllerState;
	GamePadIndex playerIndex;
};

#endif // !INPUT_H

