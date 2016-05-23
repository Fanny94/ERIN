#ifndef LINKER_H
#define LINKER_H

#include <Windows.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <math.h>
#include <vector>
#include <fstream>
#include <istream>
#include <sstream>
#include <string>
#include <DirectXMath.h>
#include "SimpleMath.h"
#include "WICTextureLoader.h"
#include <tchar.h>
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <vector>

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dcompiler.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")

using namespace DirectX::SimpleMath;
using namespace DirectX;
using namespace std;

// input
#define WIN32_LEAN_AND_MEAN
#include <XInput.h>	// XInput API
#pragma comment(lib, "XInput.lib")

#endif