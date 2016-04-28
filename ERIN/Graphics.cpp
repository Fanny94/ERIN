#include "Graphics.h"

//http://www.miguelcasillas.com/?mcportfolio=collision-detection-c
Graphics::Graphics() {}

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

	gDepthStencilView->Release();
	gDepthView->Release();

	gConstantBuffer->Release();

	customVertBuff->Release();
	this->customVertBuff = nullptr;

	this->gDevice = nullptr;
	this->gDeviceContext = nullptr;
	this->gSwapChain = nullptr;
	this->gBackbufferRTV = nullptr;

	this->gVertexLayout = nullptr;
	this->gVertexShader = nullptr;
	this->gVertexBuffer = nullptr;
	this->gPixelShader = nullptr;

	this->gConstantBuffer = nullptr;
	this->camera = nullptr;
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
	gDeviceContext->ClearDepthStencilView(gDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

	/*UINT32 vertexMS = sizeof(Vertex);

	D3D11_MAPPED_SUBRESOURCE mappedOBJ;
	HRESULT hr = gDeviceContext->Map(objBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedOBJ);
	OBJ* OBJPtr;
	OBJPtr = (OBJ*)mappedOBJ.pData;

	for (int i = 0; i < meshSubsets; ++i)
	{
		gDeviceContext->IASetIndexBuffer(meshIndexBuff, DXGI_FORMAT_R32_UINT, 0);
		gDeviceContext->IASetVertexBuffers(0, 1, &meshVertBuff, &vertexMS, &offset);

		OBJPtr->difColor = material[meshSubsetTexture[i]].difColor;
		OBJPtr->hasTexture = material[meshSubsetTexture[i]].hasTexture;

		gDeviceContext->UpdateSubresource(objBuffer, 0, NULL, &OBJPtr, 0, 0);
		gDeviceContext->PSSetConstantBuffers(0, 1, &objBuffer);

		if (material[meshSubsetTexture[i]].hasTexture)
			gDeviceContext->PSSetShaderResources(0, 1, &meshSRV[material[meshSubsetTexture[i]].texArrayIndex]);

		int indexStart = meshSubsetIndexStart[i];
		int indexDrawAmount = meshSubsetIndexStart[i + 1] - meshSubsetIndexStart[i];
		if (!material[meshSubsetTexture[i]].transparent)
			gDeviceContext->DrawIndexed(indexDrawAmount, indexStart, 0);
	}*/
}

void Graphics::RendPlayer(Matrix transform)
{
	gDeviceContext->VSSetShader(gVertexShader, nullptr, 0);
	gDeviceContext->PSSetShader(gPixelShader, nullptr, 0);

	UINT32 vertexSize = sizeof(float) * 6;
	UINT32 offset = 0;

	gDeviceContext->IASetVertexBuffers(0, 1, &gVertexBuffer, &vertexSize, &offset);
	gDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	gDeviceContext->IASetInputLayout(gVertexLayout);

	CustomUpdateBuffer(transform);

	gDeviceContext->Draw(3, 0);
}

void Graphics::RenderCustom(Mesh mesh)
{
	gDeviceContext->VSSetShader(gVertexShader, nullptr, 0);
	gDeviceContext->PSSetShader(gPixelShader, nullptr, 0);
	//Create Vertex Buffer
	D3D11_BUFFER_DESC vertexBufferDesc;
	ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));

	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexCustom) * mesh.mesh.at(0).VertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA vertexBufferData;
	ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));
	vertexBufferData.pSysMem = &mesh.mesh.at(0).vertex[0];

	hr = gDevice->CreateBuffer(&vertexBufferDesc, &vertexBufferData, &customVertBuff);

	UINT32 meshVertexSize = sizeof(VertexCustom);
	UINT32 offset = 0;

	Matrix world;

	D3D11_MAPPED_SUBRESOURCE mappedCF;
	hr = gDeviceContext->Map(customFormatBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedCF);
	CustomFormat* CFPtr;
	CFPtr = (CustomFormat*)mappedCF.pData;
	gDeviceContext->Unmap(customFormatBuffer, 0);

	for (int j = 0; j < mesh.material.size(); j++)
	{
		CFPtr->diffuseColor[0] = mesh.material.at(j).diffuseColor[0];
		CFPtr->diffuseColor[1] = mesh.material.at(j).diffuseColor[1];
		CFPtr->diffuseColor[2] = mesh.material.at(j).diffuseColor[2];
		CFPtr->ambientColor[0] = mesh.material.at(j).ambientColor[0];
		CFPtr->ambientColor[1] = mesh.material.at(j).ambientColor[1];
		CFPtr->ambientColor[2] = mesh.material.at(j).ambientColor[2];
		CFPtr->specularColor[0] = mesh.material.at(j).specularColor[0];
		CFPtr->specularColor[1] = mesh.material.at(j).specularColor[1];
		CFPtr->specularColor[2] = mesh.material.at(j).specularColor[2];
		CFPtr->shininess = mesh.material.at(j).shininess;
	}

	for (int i = 0; i < mesh.mesh.size(); i++)
	{
		gDeviceContext->IASetVertexBuffers(0, 1, &customVertBuff, &meshVertexSize, &offset);
		gDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		world = XMMatrixTranslation(mesh.mesh.at(i).Translation[0], mesh.mesh.at(i).Translation[1], mesh.mesh.at(i).Translation[2]);

		CustomUpdateBuffer(world);

		gDeviceContext->PSSetConstantBuffers(0, 1, &customFormatBuffer);

		gDeviceContext->Draw(mesh.mesh.at(i).vertex.size(), 0);
	}
}

void Graphics::CustomUpdateBuffer(Matrix transform)
{
	D3D11_MAPPED_SUBRESOURCE mapped;
	Matrix projection;
	Matrix worldViewProj;

	projection = XMMatrixPerspectiveFovLH(float(3.1415 * 0.45), float(WIDTH / HEIGHT), float(0.5), float(50));

	worldViewProj = transform * camera->camView * projection;

	worldViewProj = worldViewProj.Transpose();

	transform = transform.Transpose();

	hr = gDeviceContext->Map(gConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped);
	if (FAILED(hr))
	{
		return;
	}

	MatrixPtr2 = (MATRICES*)mapped.pData;
	MatrixPtr2->worldViewProj = worldViewProj;
	MatrixPtr2->world = transform;
	MatrixPtr2->camPos = camera->camPosition;

	gDeviceContext->Unmap(gConstantBuffer, 0);

	gDeviceContext->VSSetConstantBuffers(0, 1, &gConstantBuffer);
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
	ShowCursor(FALSE);

	HRESULT hr = D3D11CreateDeviceAndSwapChain(NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		NULL, //D3D11_CREATE_DEVICE_DEBUG,
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

		CreateDepthBuffer();

		gDevice->CreateRenderTargetView(pBackBuffer, NULL, &gBackbufferRTV);
		pBackBuffer->Release();

		gDeviceContext->OMSetRenderTargets(1, &gBackbufferRTV, gDepthStencilView);

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
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "UV", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
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

void Graphics::CreateTriangle(TriangleVertex* triangleVertices)
{
	D3D11_BUFFER_DESC bufferDesc;
	memset(&bufferDesc, 0, sizeof(bufferDesc));
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = sizeof(float) * 18;

	D3D11_SUBRESOURCE_DATA data;
	data.pSysMem = triangleVertices;
	gDevice->CreateBuffer(&bufferDesc, &data, &gVertexBuffer);
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

	D3D11_BUFFER_DESC cCFBuffer;
	ZeroMemory(&cCFBuffer, sizeof(cCFBuffer));
	cCFBuffer.Usage = D3D11_USAGE_DYNAMIC;
	cCFBuffer.ByteWidth = sizeof(CustomFormat);
	cCFBuffer.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cCFBuffer.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cCFBuffer.MiscFlags = 0;

	gDevice->CreateBuffer(&cCFBuffer, NULL, &customFormatBuffer);
}

void Graphics::CreateTriangleAABBBox(AABBBox * axisAllignedBox)
{
	for (int i = 0; i < 3; i++)
	{
		axisAllignedBox->min.x = min(axisAllignedBox->min.x, triangleVertices[i].x);
		axisAllignedBox->min.y = min(axisAllignedBox->min.y, triangleVertices[i].y);
		axisAllignedBox->min.z = min(axisAllignedBox->min.z, triangleVertices[i].z);

		axisAllignedBox->max.x = max(axisAllignedBox->max.x, triangleVertices[i].x);
		axisAllignedBox->max.y = max(axisAllignedBox->max.y, triangleVertices[i].y);
		axisAllignedBox->max.z = max(axisAllignedBox->max.z, triangleVertices[i].z);
	}

	triangleBox.push_back(*axisAllignedBox);
}

void Graphics::CreateSquareAABBBox(AABBBox * axisAllignedBox)
{
	for (int i = 0; i < vertexMeshSize.size(); i++)
	{
		axisAllignedBox->min.x = min(axisAllignedBox->min.x, vertexMeshSize[i].pos.x);
		axisAllignedBox->min.y = min(axisAllignedBox->min.y, vertexMeshSize[i].pos.y);
		axisAllignedBox->min.z = min(axisAllignedBox->min.z, vertexMeshSize[i].pos.z);

		axisAllignedBox->max.x = max(axisAllignedBox->max.x, vertexMeshSize[i].pos.x);
		axisAllignedBox->max.y = max(axisAllignedBox->max.y, vertexMeshSize[i].pos.y);
		axisAllignedBox->max.z = max(axisAllignedBox->max.z, vertexMeshSize[i].pos.z);
	}

	squareBox.push_back(*axisAllignedBox);

}

void Graphics::CreateDepthBuffer()
{
	D3D11_TEXTURE2D_DESC depthDesc;
	depthDesc.Width = WIDTH;
	depthDesc.Height = HEIGHT;
	depthDesc.MipLevels = 1;
	depthDesc.ArraySize = 1;
	depthDesc.Format = DXGI_FORMAT_D32_FLOAT;
	depthDesc.SampleDesc.Count = 4;
	depthDesc.SampleDesc.Quality = 0;
	depthDesc.Usage = D3D11_USAGE_DEFAULT;
	depthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthDesc.CPUAccessFlags = 0;
	depthDesc.MiscFlags = 0;

	gDevice->CreateTexture2D(&depthDesc, 0, &gDepthView);

	gDevice->CreateDepthStencilView(gDepthView, 0, &gDepthStencilView);

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

	world = XMMatrixRotationZ(XMConvertToRadians(0)) * XMMatrixTranslation(0, 0, 0);
	projection = XMMatrixPerspectiveFovLH(float(3.1415 * 0.45), float(WIDTH / HEIGHT), float(0.5), float(50));

	viewProj = camera->camView * projection;

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
	MatrixPtr->camPos = camera->camPosition;

	gDeviceContext->Unmap(gConstantBuffer, 0);

	gDeviceContext->VSSetConstantBuffers(0, 1, &gConstantBuffer);
}