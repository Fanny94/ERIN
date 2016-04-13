#ifndef INPUT_H
#define INPUT_H
#include "Linker.h"


typedef enum
{
	GamePadIndex_One = 0,
	GamePadIndex_Two = 1,
	GamePadIndex_Three = 2,
	GamePadIndex_Four = 3,
}GamePadIndex;

//definition of buttons
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
		_left_thumbstick = Vector2(0.0f);
		_right_thumbstick = Vector2(0.0f);
		_left_trigger = _right_trigger = 0.0f;
	}
};

class Input
{
public:
	Input(GamePadIndex player);
	virtual ~Input(void);

	bool isConnected();
	void vibrate(float leftmotor = 0.0f, float rightmotor = 0.0f);
	void update();

	GamePadState State;

private:
	XINPUT_STATE _controllerState;
	GamePadIndex playerIndex;
};

#endif // !INPUT_H

