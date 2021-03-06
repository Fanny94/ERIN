#include "Camera.h"
#include "Input.h"

Camera::Camera() {}

Camera::~Camera()
{
	DIKeyboard->Unacquire();
	DIMouse->Unacquire();
	DirectInput->Release();
}

bool Camera::InitDirectInput(HINSTANCE hInstance)
{
	hr = DirectInput8Create(hInstance,
		DIRECTINPUT_VERSION,
		IID_IDirectInput8, (void**)&DirectInput,
		NULL);

	hr = DirectInput->CreateDevice(GUID_SysKeyboard,
		&DIKeyboard,
		NULL);

	hr = DirectInput->CreateDevice(GUID_SysMouse,
		&DIMouse,
		NULL);

	hr = DIKeyboard->SetDataFormat(&c_dfDIKeyboard);
	hr = DIKeyboard->SetCooperativeLevel(wndH, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

	hr = DIMouse->SetDataFormat(&c_dfDIMouse);
	hr = DIMouse->SetCooperativeLevel(wndH, DISCL_EXCLUSIVE | DISCL_NOWINKEY | DISCL_FOREGROUND);

	return true;
}

void Camera::DetectInput(double time)
{
	speed = (float)(5.0f * time);

	DIMOUSESTATE mouseCurrState;

	BYTE keyboardState[256];

	DIKeyboard->Acquire();
	DIMouse->Acquire();

	DIMouse->GetDeviceState(sizeof(DIMOUSESTATE), &mouseCurrState);
	DIKeyboard->GetDeviceState(sizeof(keyboardState), (LPVOID)&keyboardState);

	if (keyboardState[DIK_A] & 0x80)
		moveLeftRight -= speed;

	if (keyboardState[DIK_D] & 0x80)
		moveLeftRight += speed;

	if (keyboardState[DIK_W] & 0x80)
		moveBackForward += speed;

	if (keyboardState[DIK_S] & 0x80)
		moveBackForward -= speed;

	if (keyboardState[DIK_Q] & 0x80)
		moveUpDown += speed;

	if (keyboardState[DIK_E] & 0x80)
		moveUpDown -= speed;

	if (keyboardState[DIK_C] & 0x80)
	{
		if ((mouseCurrState.lX != mouseLastState.lX) || (mouseCurrState.lY != mouseLastState.lY))
		{
			camYaw += mouseLastState.lX * 0.001f;
			camPitch += mouseCurrState.lY * 0.001f;
			mouseLastState = mouseCurrState;
		}

	}

	if (keyboardState[DIK_V] & 0x80)
	{
		camYaw = 0.0f;
		camPitch = 0.0f;

	}

	UpdateCamera();
}

void Camera::InitCamera()
{
	frameCount++;

	if (GetTime() > 1.0f)
	{
		Fps = frameCount;
		frameCount = 0;
		StartTimer();
	}

	frameTime = GetFrameTime();

	DetectInput(frameTime);
}

void Camera::UpdateCamera()
{
	camRotationMatrix = XMMatrixRotationRollPitchYaw(camPitch, camYaw, 0);
	camTarget = XMVector3TransformCoord(worldForward, camRotationMatrix);
	camTarget = XMVector3Normalize(camTarget);

	Matrix RotateYTempMatrix;
	RotateYTempMatrix = XMMatrixRotationY(camYaw);

	camRight = XMVector3TransformCoord(worldRight, RotateYTempMatrix);
	camUp = XMVector3TransformCoord(camUp, RotateYTempMatrix);
	camForward = XMVector3TransformCoord(worldForward, RotateYTempMatrix);

	camPosition += moveLeftRight*camRight;
	camPosition += moveBackForward*camForward;
	camPosition += moveUpDown*camUp;

	moveLeftRight = 0.0f;
	moveBackForward = 0.0f;
	moveUpDown = 0.0f;

	camTarget = camPosition + camTarget;

	camView = XMMatrixLookAtLH(camPosition, camTarget, camUp);
}

void Camera::UpdateGameCamera(float x, float y, double dt)
{
	// The Game camera that is going to follow the player and allways showing the elevator

	camPosition.x += ((x / 2) - camPosition.x) * lerp * dt;
	camPosition.y += ((y / 2) - camPosition.y) * lerp * dt;
}

void Camera::ResetCamera()
{
	camPosition = Vector4(0.0f, 0.5f, -18.0f, 1.0f);
}

void Camera::cameraMoveLeft()
{
	moveLeftRight -= speed;
}

void Camera::cameraMoveRight()
{
	moveLeftRight += speed;
}

void Camera::cameraMoveUp()
{
	moveUpDown += speed;
}
void Camera::cameraMoveDown()
{
	moveUpDown -= speed;
}

void Camera::cameraMoveLeft(float factor)
{
	moveLeftRight -= speed * -factor;
}

void Camera::cameraMoveRight(float factor)
{
	moveLeftRight += speed * factor;
}

void Camera::cameraMoveUp(float factor)
{
	moveUpDown += speed * factor;
}
void Camera::cameraMoveDown(float factor)
{
	moveUpDown -= speed * -factor;
}

void Camera::cameraFollow(float x, float y)
{
	this->camPosition.x = x;
	this->camPosition.y = y;
}

void Camera::StartTimer()
{
	LARGE_INTEGER frequencyCount;
	QueryPerformanceFrequency(&frequencyCount);			//Gets the time in counts per second

	countsPerSecond = double(frequencyCount.QuadPart);	//Stores the counts per second

	QueryPerformanceCounter(&frequencyCount);			//Gets the current time in counts
	counterStart = frequencyCount.QuadPart;				//Stores the start of the count
}

double Camera::GetTime()
{
	LARGE_INTEGER currentTime;
	QueryPerformanceCounter(&currentTime);				//Gets the current time in counts
	return double(currentTime.QuadPart - counterStart) / countsPerSecond;
}

double Camera::GetFrameTime()
{
	LARGE_INTEGER currentTime;
	__int64 tickCount;
	QueryPerformanceCounter(&currentTime);				//Gets the current time in counts

	tickCount = currentTime.QuadPart - frameTimeOld;	//Stores the time it took from the last frame to this frame
	frameTimeOld = currentTime.QuadPart;				//Stores this frame as the next last frame

	if (tickCount < 0.0f)
		tickCount = (__int64)0.0f;

	return float(tickCount) / countsPerSecond;
}