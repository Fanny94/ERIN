#include "Engine.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

Engine::Engine()
{
}

Engine::~Engine()
{
	gBackbufferRTV->Release();
	gSwapChain->Release();
	gDevice->Release();
	gDeviceContext->Release();

	gVertexLayout->Release();
	gVertexShader->Release();
	gVertexBuffer->Release();
	gPixelShader->Release();

	gConstantBuffer->Release();
}

int Engine::Run(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCommandLine, int nCommandShow)
{
	MSG msg = { 0 };

	//create window
	HWND wndHandle = InitWindow(hInstance); //Create Window

											//window is valid
	if (wndHandle)
	{
		//Create SwapChain, Device and Device Context 
		CreateDirect3DContext(wndHandle);

		SetViewport(); //Set Viewport

		CreateShaders();

		CreateTriangle();

		CreateConstantBuffer();

		ShowWindow(wndHandle, nCommandShow);

		while (WM_QUIT != msg.message)
		{
			//read messages
			if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);

				DispatchMessage(&msg);
			}
			else
			{
				//update/render

				UpdateConstantBuffer();

				Render();

				//switch front- and back-buffer
				gSwapChain->Present(0, 0);
			}
		}
		//finish program
		DestroyWindow(wndHandle);
	}
	//return how the program finished
	return (int)msg.wParam;
}

void Engine::SetViewport()
{
	D3D11_VIEWPORT vp;
	vp.Width = WIDTH;
	vp.Height = HEIGHT;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;

	gDeviceContext->RSSetViewports(1, &vp);
}

void Engine::Render()
{
	float clearColor[] = { 0, 0, 1, 1 };
	gDeviceContext->ClearRenderTargetView(gBackbufferRTV, clearColor);


	gDeviceContext->VSSetShader(gVertexShader, nullptr, 0);
	gDeviceContext->HSSetShader(nullptr, nullptr, 0);
	gDeviceContext->DSSetShader(nullptr, nullptr, 0);
	gDeviceContext->GSSetShader(nullptr, nullptr, 0);
	gDeviceContext->PSSetShader(gPixelShader, nullptr, 0);

	UINT32 vertexSize = sizeof(float) * 6;
	UINT32 offset = 0;
	gDeviceContext->IASetVertexBuffers(0, 1, &gVertexBuffer, &vertexSize, &offset);
	gDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	gDeviceContext->IASetInputLayout(gVertexLayout);

	gDeviceContext->Draw(3, 0);
}

HWND Engine::InitWindow(HINSTANCE hInstance)
{
	//Every window created must belkong to a class

	WNDCLASSEX winClassInfo = { 0 };
	winClassInfo.cbSize = sizeof(WNDCLASSEX);
	winClassInfo.style = CS_HREDRAW | CS_VREDRAW;
	winClassInfo.lpfnWndProc = WndProc; //This function is called for events
	winClassInfo.hInstance = hInstance;
	winClassInfo.lpszClassName = "WindowClass";
	//Window is the name of the class

	if (!RegisterClassEx(&winClassInfo))
		return false;

	//the window size
	RECT rc = { 0, 0, WIDTH, HEIGHT };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

	HWND handle = CreateWindow(
		"WindowClass",	//Class name
		"Window",		//Window name
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		rc.right - rc.left,
		rc.bottom - rc.top,
		nullptr,
		nullptr,
		hInstance,
		nullptr);

	return handle;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	//call the default handler function if w do not handle the message here 
	return DefWindowProc(hWnd, message, wParam, lParam);
}

HRESULT Engine::CreateDirect3DContext(HWND wndHandle)
{
	//struct that holds info about the swapchain
	DXGI_SWAP_CHAIN_DESC swapChainD;

	//clear out the struct for use
	ZeroMemory(&swapChainD, sizeof(DXGI_SWAP_CHAIN_DESC));

	swapChainD.BufferCount = 1;
	swapChainD.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainD.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainD.OutputWindow = wndHandle;
	swapChainD.SampleDesc.Count = 4;
	swapChainD.Windowed = TRUE;

	HRESULT hr = D3D11CreateDeviceAndSwapChain(NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		D3D11_CREATE_DEVICE_DEBUG,
		NULL,
		NULL,
		D3D11_SDK_VERSION,
		&swapChainD,
		&gSwapChain,
		&gDevice,
		NULL,
		&gDeviceContext);

	if (SUCCEEDED(hr))
	{
		ID3D11Texture2D* pBackBuffer = nullptr;
		gSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

		gDevice->CreateRenderTargetView(pBackBuffer, NULL, &gBackbufferRTV);
		pBackBuffer->Release();

		gDeviceContext->OMSetRenderTargets(1, &gBackbufferRTV, NULL);

	}
	return hr;
}

void Engine::CreateShaders()
{
	ID3DBlob* pVS = nullptr;
	D3DCompileFromFile(
		L"VertexShader.hlsl", // filename
		nullptr,		// optional macros
		nullptr,		// optional include files
		"VS_main",		// entry point
		"vs_4_0",		// shader model (target)
		0,				// shader compile options
		0,				// effect compile options
		&pVS,			// double pointer to ID3DBlob
		nullptr			// pointer for Error Blob messages.			
		);

	D3D11_INPUT_ELEMENT_DESC inputDesc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	gDevice->CreateInputLayout(inputDesc,
		ARRAYSIZE(inputDesc), pVS->GetBufferPointer(), pVS->GetBufferSize(), &gVertexLayout);

	gDevice->CreateVertexShader(pVS->GetBufferPointer(), pVS->GetBufferSize(), nullptr, &gVertexShader);
	pVS->Release();

	ID3DBlob* pPS = nullptr;
	D3DCompileFromFile(
		L"PixelShader.hlsl", // filename
		nullptr,		// optional macros
		nullptr,		// optional include files
		"PS_main",		// entry point
		"ps_4_0",		// shader model (target)
		0,				// shader compile options
		0,				// effect compile options
		&pPS,			// double pointer to ID3DBlob
		nullptr			// pointer for Error Blob messages.			
		);


	gDevice->CreatePixelShader(pPS->GetBufferPointer(), pPS->GetBufferSize(), nullptr, &gPixelShader);
	pPS->Release();

}

void Engine::CreateTriangle()
{

	TriangleVertex triangleVertices[3] =
	{
		0.0f, 0.5f, 0.0f,	//v0 pos
		1.0f, 0.0f, 0.0f,	//v0 color

		0.5f, -0.5f, 0.0f,	//v1
		0.0f, 1.0f, 0.0f,	//v1 color

		-0.5f, -0.5f, 0.0f, //v2
		0.0f, 0.0f, 1.0f	//v2 color
	};

	D3D11_BUFFER_DESC bufferDesc;
	memset(&bufferDesc, 0, sizeof(bufferDesc));
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = sizeof(triangleVertices);

	D3D11_SUBRESOURCE_DATA data;
	data.pSysMem = triangleVertices;
	gDevice->CreateBuffer(&bufferDesc, &data, &gVertexBuffer);

}

void Engine::CreateConstantBuffer()
{
	D3D11_BUFFER_DESC cBufferDesc;
	memset(&cBufferDesc, 0, sizeof(cBufferDesc));
	cBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	cBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	cBufferDesc.ByteWidth = sizeof(MATRICES);

	gDevice->CreateBuffer(&cBufferDesc, NULL, &gConstantBuffer);
}

void Engine::UpdateConstantBuffer()
{
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mapped;
	MATRICES* MatrixPtr;

	static float rotationCount;
	rotationCount += 0.01;

	Matrix world;
	Matrix view;
	Matrix projection;
	Matrix worldViewProj;

	Vector3 camPos = Vector3(0, 0, -2);
	Vector3 focusPos = Vector3(0, 0, 0);
	Vector3 UpDir = Vector3(0, 1, 0);

	world = XMMatrixRotationZ(XMConvertToRadians(rotationCount));
	projection = XMMatrixPerspectiveFovLH(float(3.1415 * 0.45), float(WIDTH / HEIGHT), float(0.5), float(50));
	view = XMMatrixLookAtLH(camPos, focusPos, UpDir);

	worldViewProj = world * view * projection;

	worldViewProj = worldViewProj.Transpose();

	world = world.Transpose();

	result = gDeviceContext->Map(gConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped);
	if (FAILED(result))
	{
		return;
	}

	MatrixPtr = (MATRICES*)mapped.pData;
	MatrixPtr->worldViewProj = worldViewProj;
	MatrixPtr->world = world;

	gDeviceContext->Unmap(gConstantBuffer, 0);

	gDeviceContext->VSSetConstantBuffers(0, 1, &gConstantBuffer);
}


