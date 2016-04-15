#ifndef CAMERA_H
#define CAMERA_H

#include "Linker.h"
class Graphics;

class Camera
{
public:
	Camera();
	~Camera();
	
	// Vectors
	Vector4 worldForward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	Vector4 worldRight	= XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	Vector4 camForward	= XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	Vector4 camRight = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	Vector4 camTarget = XMVectorSet(0.0f, 0.0f, 1.0f, 1.0f);
	Vector4 camUp = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	Vector4 camPosition = XMVectorSet(0.0f, 0.0f, -2.0f, 1.0f);

	// Matrices
	Matrix camRotationMatrix;
	Matrix groundWorld;
	Matrix camView;

	// Movement
	float moveLeftRight	= 0.0f;
	float moveBackForward = 0.0f;
	float moveUpDown = 0.0f;
	float camYaw = 0.0f;
	float camPitch = 0.0f;
	float speed;

	int frameCount = 0;
	__int64 counterStart = 0;
	__int64 frameTimeOld = 0;
	int Fps = 0;

	double countsPerSecond = 0.0;
	double frameTime;

	HRESULT hr;
	HWND wndH = NULL;
	// Update camera
	void DetectInput(double time);
	void StartTimer();
	double GetTime();
	double GetFrameTime();
	void InitCamera();
	void UpdateCamera();
	void cameraMoveLeft();
	void cameraMoveRight();
	void cameraMoveUp();
	void cameraMoveDown();
	bool getInput() { return cameraInput; };
	bool InitDirectInput(HINSTANCE hInstance);

	IDirectInputDevice8* DIKeyboard;
	IDirectInputDevice8* DIMouse;

	DIMOUSESTATE mouseLastState;
	LPDIRECTINPUT8 DirectInput;
	bool cameraInput;

private:

};

#endif