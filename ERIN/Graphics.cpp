#include "Graphics.h"
#include "Camera.h"

Graphics::Graphics()
{

}

Graphics::~Graphics()
{
	gDevice->Release();
	gDeviceContext->Release();
	gSwapChain->Release();
	gBackbufferRTV->Release();

	gVertexLayout->Release();
	gVertexShader->Release();
	gVertexBuffer->Release();
	gPixelShader->Release();

	gConstantBuffer->Release();
}

void Graphics::SetViewport()
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

void Graphics::Render()
{
	float clearColor[] = { 1, 1, 0, 1 };
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

HRESULT Graphics::CreateDirect3DContext(HWND wndHandle)
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

void Graphics::CreateShaders()
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

void Graphics::CreateTriangle()
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

void Graphics::CreateConstantBuffer()
{
	D3D11_BUFFER_DESC cBufferDesc;
	memset(&cBufferDesc, 0, sizeof(cBufferDesc));
	cBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	cBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	cBufferDesc.ByteWidth = sizeof(MATRICES);

	gDevice->CreateBuffer(&cBufferDesc, NULL, &gConstantBuffer);
}

void Graphics::UpdateConstantBuffer()
{

	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mapped;

	static float rotationCount;
	rotationCount += 0.01f;

	Matrix world;
	Matrix projection;
	Matrix worldViewProj;

	world = XMMatrixRotationZ(XMConvertToRadians(rotationCount)) * XMMatrixTranslation(0, 0, 0);
	projection = XMMatrixPerspectiveFovLH(float(3.1415 * 0.45), float(WIDTH / HEIGHT), float(0.5), float(50));

	worldViewProj = world * camera->camView * projection;

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