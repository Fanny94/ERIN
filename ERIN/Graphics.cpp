#include "Graphics.h"

//http://www.miguelcasillas.com/?mcportfolio=collision-detection-c
Graphics::Graphics()
{
	axisAllignedBox.min = { FLT_MAX, FLT_MAX, FLT_MAX };
	axisAllignedBox.max = { -FLT_MAX, -FLT_MAX, -FLT_MAX };

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

	vertAABBBuffer->Release();
	AABBLayout->Release();
	AABBVertexShader->Release();
	AABBPixelShader->Release();

	triangleAABBVertexBuffer->Release();

	gDepthView->Release();
	gDepthStencilView->Release();

	gConstantBuffer->Release();
	objBuffer->Release();

	/*customVertBuff->Release();
	this->customVertBuff = nullptr;*/

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

	/*gDeviceContext->VSSetShader(gVertexShader, nullptr, 0);
	gDeviceContext->PSSetShader(gPixelShader, nullptr, 0);*/

	/*UINT32 vertexSize = sizeof(float) * 6;
	UINT32 offset = 0;*/
	/*gDeviceContext->IASetVertexBuffers(0, 1, &gVertexBuffer, &vertexSize, &offset);
	gDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	gDeviceContext->IASetInputLayout(gVertexLayout);

	gDeviceContext->Draw(3, 0);*/

	/*UINT32 vertexMS = sizeof(Vertex);
>>>>>>> refs/remotes/origin/master

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

	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mapped;

	Matrix world;
	Matrix projection;
	Matrix worldViewProj;

	//world = XMMatrixRotationZ(XMConvertToRadians(0)) * XMMatrixTranslation(0, 0, 0);
	projection = XMMatrixPerspectiveFovLH(float(3.1415 * 0.45), float(WIDTH / HEIGHT), float(0.5), float(50));

	// viewProj = camera->camView * projection;

	worldViewProj = transform * camera->camView * projection;

	worldViewProj = worldViewProj.Transpose();

	transform = transform.Transpose();

	result = gDeviceContext->Map(gConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped);
	if (FAILED(result))
	{
		return;
	}

	MatrixPtr2 = (MATRICES*)mapped.pData;
	MatrixPtr2->worldViewProj = worldViewProj;
	MatrixPtr2->world = transform;

	gDeviceContext->Unmap(gConstantBuffer, 0);

	gDeviceContext->VSSetConstantBuffers(0, 1, &gConstantBuffer);

	gDeviceContext->Draw(3, 0);
}

void Graphics::RendBullet(Matrix transform)
{

	gDeviceContext->VSSetShader(gVertexShader, nullptr, 0);
	gDeviceContext->PSSetShader(gPixelShader, nullptr, 0);

	UINT32 vertexSize = sizeof(float) * 6;
	UINT32 offset = 0;

	gDeviceContext->IASetVertexBuffers(0, 1, &gVertexBuffer, &vertexSize, &offset);
	gDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	gDeviceContext->IASetInputLayout(gVertexLayout);

	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mapped;

	Matrix world;
	Matrix projection;
	Matrix worldViewProj;

	//world = XMMatrixRotationZ(XMConvertToRadians(0)) * XMMatrixTranslation(0, 0, 0);
	projection = XMMatrixPerspectiveFovLH(float(3.1415 * 0.45), float(WIDTH / HEIGHT), float(0.5), float(50));

	// viewProj = camera->camView * projection;

	worldViewProj = transform * camera->camView * projection;

	worldViewProj = worldViewProj.Transpose();

	transform = transform.Transpose();

	result = gDeviceContext->Map(gConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped);
	if (FAILED(result))
	{
		return;
	}

	MatrixPtr2 = (MATRICES*)mapped.pData;
	MatrixPtr2->worldViewProj = worldViewProj;
	MatrixPtr2->world = transform;

	gDeviceContext->Unmap(gConstantBuffer, 0);

	gDeviceContext->VSSetConstantBuffers(0, 1, &gConstantBuffer);

	gDeviceContext->Draw(3, 0);
}
//---------------------------------------------------------------------------
void Graphics::RendAABB()
{
	gDeviceContext->VSSetShader(AABBVertexShader, nullptr, 0);
	gDeviceContext->PSSetShader(AABBPixelShader, nullptr, 0);

	UINT32 vertexSize = sizeof(XMFLOAT3);
	UINT32 offset = 0;

	gDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	gDeviceContext->IASetInputLayout(AABBLayout);

	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mapped;

	Matrix world;
	Matrix projection;
	Matrix worldViewProj;

	world = XMMatrixRotationZ(XMConvertToRadians(0)) * XMMatrixTranslation(0, 0, 0.5);
	projection = XMMatrixPerspectiveFovLH(float(3.1415 * 0.45), float(WIDTH / HEIGHT), float(0.5), float(50));

	// viewProj = camera->camView * projection;

	worldViewProj = world * camera->camView * projection;

	worldViewProj = worldViewProj.Transpose();

	world = world.Transpose();

	result = gDeviceContext->Map(gConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped);
	if (FAILED(result))
	{
		return;
	}

	MatrixPtr2 = (MATRICES*)mapped.pData;
	MatrixPtr2->worldViewProj = worldViewProj;
	MatrixPtr2->world = world;

	gDeviceContext->Unmap(gConstantBuffer, 0);

	gDeviceContext->IASetVertexBuffers(0, 1, &vertAABBBuffer, &vertexSize, &offset);
	gDeviceContext->VSSetConstantBuffers(0, 1, &gConstantBuffer);
	gDeviceContext->Draw(24, 0);

}
void Graphics::RendTriangleAABB(Matrix transform)
{
	gDeviceContext->VSSetShader(AABBVertexShader, nullptr, 0);
	gDeviceContext->PSSetShader(AABBPixelShader, nullptr, 0);

	UINT32 vertexSize = sizeof(XMFLOAT3);
	UINT32 offset = 0;

	gDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	gDeviceContext->IASetInputLayout(AABBLayout);

	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mapped;

	Matrix world;
	Matrix projection;
	Matrix worldViewProj;

	//world = XMMatrixRotationZ(XMConvertToRadians(0)) * XMMatrixTranslation(0, 0, 0);
	projection = XMMatrixPerspectiveFovLH(float(3.1415 * 0.45), float(WIDTH / HEIGHT), float(0.5), float(50));

	// viewProj = camera->camView * projection;

	worldViewProj = transform * camera->camView * projection;

	worldViewProj = worldViewProj.Transpose();

	//world = world.Transpose();

	result = gDeviceContext->Map(gConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped);
	if (FAILED(result))
	{
		return;
	}

	MatrixPtr2 = (MATRICES*)mapped.pData;
	MatrixPtr2->worldViewProj = worldViewProj;
	MatrixPtr2->world = world;

	gDeviceContext->Unmap(gConstantBuffer, 0);

	gDeviceContext->IASetVertexBuffers(0, 1, &triangleAABBVertexBuffer, &vertexSize, &offset);
	gDeviceContext->VSSetConstantBuffers(0, 1, &gConstantBuffer);
	gDeviceContext->Draw(8, 0);

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

	for (int i = 0; i < mesh.mesh.size(); i++)
	{
		gDeviceContext->IASetVertexBuffers(0, 1, &customVertBuff, &meshVertexSize, &offset);
		gDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		gDeviceContext->Draw(mesh.mesh.at(i).vertex.size(), 0);
	}
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

//----------------------------------------------------------------------------------
	//AABB vertexShader
	ID3DBlob* pVS_2 = nullptr;
	D3DCompileFromFile(
		L"AABBVertexShader.hlsl", // filename
		nullptr,		// optional macros
		nullptr,		// optional include files
		"VS_main",		// entry point
		"vs_4_0",		// shader model (target)
		0,				// shader compile options
		0,				// effect compile options
		&pVS_2,			// double pointer to ID3DBlob
		nullptr			// pointer for Error Blob messages.			
		);

	D3D11_INPUT_ELEMENT_DESC AABBinputDesc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },

	};

	gDevice->CreateInputLayout(AABBinputDesc,
		ARRAYSIZE(AABBinputDesc), pVS_2->GetBufferPointer(), pVS_2->GetBufferSize(), &AABBLayout);

	gDevice->CreateVertexShader(pVS_2->GetBufferPointer(), pVS_2->GetBufferSize(), nullptr, &AABBVertexShader);
	pVS_2->Release();

	//AABBPixelShader
	ID3DBlob* pPS_2 = nullptr;
	D3DCompileFromFile(
		L"AABBPixelShader.hlsl", // filename
		nullptr,		// optional macros
		nullptr,		// optional include files
		"PS_main",		// entry point
		"ps_4_0",		// shader model (target)
		0,				// shader compile options
		0,				// effect compile options
		&pPS_2,			// double pointer to ID3DBlob
		nullptr			// pointer for Error Blob messages.			
		);

	gDevice->CreatePixelShader(pPS_2->GetBufferPointer(), pPS_2->GetBufferSize(), nullptr, &AABBPixelShader);
	pPS_2->Release();

//----------------------------------------------------------------------------------
}

void Graphics::CreateDepthBuffer()
{
	D3D11_TEXTURE2D_DESC desc;
	desc.Width = WIDTH;
	desc.Height = HEIGHT;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_D32_FLOAT;
	desc.SampleDesc.Count = 4;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;

	gDevice->CreateTexture2D(&desc, 0, &gDepthView);

	gDevice->CreateDepthStencilView(gDepthView, 0, &gDepthStencilView);

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

	D3D11_BUFFER_DESC cOBJBufferDesc;
	ZeroMemory(&cOBJBufferDesc, sizeof(D3D11_BUFFER_DESC));
	cOBJBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	cOBJBufferDesc.ByteWidth = sizeof(OBJ);
	cOBJBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cOBJBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cOBJBufferDesc.MiscFlags = 0;

	gDevice->CreateBuffer(&cOBJBufferDesc, NULL, &objBuffer);

}

void Graphics::CreateTriangleAABBBox(TriangleVertex* triangleVertices)
{
	//This function defines an AABB box for the triangle with a min and a max value

	for (int i = 0; i < 3; i++)
	{
		//min
		//left bottom corner (front)
		if (triangleVertices[i].x < triAxis.min.x)
		{
			triAxis.min.x = triangleVertices[i].x;
		}
		if (triangleVertices[i].y < triAxis.min.y)
		{
			triAxis.min.y = triangleVertices[i].y;
		}
		if (triangleVertices[i].z < triAxis.min.z)
		{
			triAxis.min.z = triangleVertices[i].z;
		}

		//max
		//right upper corner (back)
		if (triangleVertices[i].x > triAxis.max.x)
		{
			triAxis.max.x = triangleVertices[i].x;
		}
		if (triangleVertices[i].y > triAxis.max.y)
		{
			triAxis.max.y = triangleVertices[i].y;
		}
		if (triangleVertices[i].z > triAxis.max.z)
		{
			triAxis.max.z = triangleVertices[i].z;
		}

		//points is an array of 8 points that later will represent the 4 corners of the AABB triangle
		triVertexArray.points[0] = triAxis.min;
		triVertexArray.points[3] = triAxis.max;
	}

	//squareBox.push_back(AABBVertexArray);
}
void Graphics::AABBTrianglePoints()
{
	//diference between Min and Max
	float diffX = abs(triVertexArray.points[3].x) - abs(triVertexArray.points[0].x);
	float diffY = abs(triVertexArray.points[3].y) - abs(triVertexArray.points[0].y);
	float diffZ = abs(triVertexArray.points[3].z) - abs(triVertexArray.points[0].z);


	//points[0, 1, 2, 3] is the corners of the triangle's AABB 
	triVertexArray.points[1].x = triVertexArray.points[3].x;
	triVertexArray.points[1].y = triVertexArray.points[0].y;
	triVertexArray.points[1].z = triVertexArray.points[0].z;
	
	triVertexArray.points[2].x = triVertexArray.points[0].x;
	triVertexArray.points[2].y = triVertexArray.points[3].y;
	triVertexArray.points[2].z = triVertexArray.points[0].z;

	//to define the lines the same vertices is going to be used several times
	//that's why we get 8 vertices that is going to be drawn for the AABB triangle
	//Define lines
	triAABBBuffer.points[0] = triVertexArray.points[0];
	triAABBBuffer.points[1] = triVertexArray.points[1];

	triAABBBuffer.points[2] = triVertexArray.points[0];
	triAABBBuffer.points[3] = triVertexArray.points[2];

	triAABBBuffer.points[4] = triVertexArray.points[1];
	triAABBBuffer.points[5] = triVertexArray.points[3];

	triAABBBuffer.points[6] = triVertexArray.points[2];
	triAABBBuffer.points[7] = triVertexArray.points[3];

	//pushback points for the lines in the vector that is going to be used in the vertex buffer
	triangleVertexArray.push_back(triAABBBuffer);

	D3D11_BUFFER_DESC vertexBufferDesc;
	ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));

	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(AABBVertex);
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA vertexBufferData;
	ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));
	vertexBufferData.pSysMem = &triangleVertexArray[0];

	//We store the points in the triangleVertexBuffer anhd then use it in the render function to be able to render this
	gDevice->CreateBuffer(&vertexBufferDesc, &vertexBufferData, &triangleAABBVertexBuffer);

}

//AABBBox* Graphics::transformBoundingBox(Matrix transform)
//{
//
//	//.Right returns the first column vector of the matrix
//	float xa = transform.Right * triVertexArray.points[0].x;
//	float xb = transform.Right * triVertexArray.points[3].x;
//
//	//.Up returns the second column 
//	float ya = transform.Up * triVertexArray.points[0].y;
//	float yb = transform.Up * triVertexArray.points[3].y;
//
//	//.Backward returns the third column 
//	float za = transform.Backward * triVertexArray.points[0].z;
//	float zb = transform.Backward * triVertexArray.points[3].z;
//
//	float minValue[3] = { min(xa, xb) + min(ya, yb) + min(za, zb) };
//	float maxValue[3] = { max(xa, xb) + max(ya, yb) + max(za, zb) };
//	
//	newAABB = new AABBBox();
//		
//	return newAABB->points[0] = minValue + transform.Translation,
//		newAABB->points[3] = maxValue + transform.Translation;
//	
//
//}

void Graphics::CreateSquareAABBBox()
{
	//This function defines an AABB box for the cube with a min and a max value

	for (int i = 0; i < vertexMeshSize.size(); i++)
	{
		//min
		//left bottom corner (front)
		if (vertexMeshSize[i].pos.x < axisAllignedBox.min.x)
		{
			axisAllignedBox.min.x = vertexMeshSize[i].pos.x;
		}
		if (vertexMeshSize[i].pos.y < axisAllignedBox.min.y)
		{
			axisAllignedBox.min.y = vertexMeshSize[i].pos.y;
		}
		if (vertexMeshSize[i].pos.z < axisAllignedBox.min.z)
		{
			axisAllignedBox.min.z = vertexMeshSize[i].pos.z;
		}
	
		//max
		//right upper corner (back)
		if (vertexMeshSize[i].pos.x > axisAllignedBox.max.x)
		{
			axisAllignedBox.max.x = vertexMeshSize[i].pos.x;
		}
		if (vertexMeshSize[i].pos.y > axisAllignedBox.max.y)
		{
			axisAllignedBox.max.y = vertexMeshSize[i].pos.y;
		}
		if (vertexMeshSize[i].pos.z > axisAllignedBox.max.z)
		{
			axisAllignedBox.max.z = vertexMeshSize[i].pos.z;
		}

		//points is an array of 8 points that later will represent the 8 corners of the AABB cube 
		AABBVertexArray.points[0] = axisAllignedBox.min;
		AABBVertexArray.points[7] = axisAllignedBox.max;
	}

	//squareBox.push_back(AABBVertexArray);

}
void Graphics::AABBSquarePoints()
{

	//This function defines the rest of the points of the AABB cube, including min and max

	//diference between Min and Max
	float diffX = abs(AABBVertexArray.points[7].x) - abs(AABBVertexArray.points[0].x);
	float diffY = abs(AABBVertexArray.points[7].y) - abs(AABBVertexArray.points[0].y);
	float diffZ = abs(AABBVertexArray.points[7].z) - abs(AABBVertexArray.points[0].z);


	//points[0, 1, 2, 3, 4, 5, 6, 7] is the 8 corners of the cube's AABB 
	//Left Upper Corner (front)
	AABBVertexArray.points[1].x = AABBVertexArray.points[0].x;
	AABBVertexArray.points[1].y = AABBVertexArray.points[7].y - diffY;
	AABBVertexArray.points[1].z = AABBVertexArray.points[0].z;

	//Right upper corner (front)
	AABBVertexArray.points[2].x = AABBVertexArray.points[7].x;
	AABBVertexArray.points[2].y = AABBVertexArray.points[1].y;
	AABBVertexArray.points[2].z = AABBVertexArray.points[0].z;

	//Right Bottom corner (front) 
	AABBVertexArray.points[3].x = AABBVertexArray.points[2].x;
	AABBVertexArray.points[3].y = AABBVertexArray.points[0].y;
	AABBVertexArray.points[3].z = AABBVertexArray.points[0].z;

	//Right bottom corner (back)
	AABBVertexArray.points[4].x = AABBVertexArray.points[7].x;
	AABBVertexArray.points[4].y = AABBVertexArray.points[0].y;
	AABBVertexArray.points[4].z = AABBVertexArray.points[3].z - diffZ;
	
	//Left bottom corner (back)
	AABBVertexArray.points[5].x = AABBVertexArray.points[4].x - diffX;
	AABBVertexArray.points[5].y = AABBVertexArray.points[0].y;
	AABBVertexArray.points[5].z = AABBVertexArray.points[4].z;

	//Left upper corner (back)
	AABBVertexArray.points[6].x = AABBVertexArray.points[7].x - diffX;
	AABBVertexArray.points[6].y = AABBVertexArray.points[7].y;
	AABBVertexArray.points[6].z = AABBVertexArray.points[0].z - diffZ;


//buffer array with definition of the lines
//Here there are 24 vertices that is going to be drawn because we use a vertex buffer to draw the lines
//first quadrant (first)
	//line 1
	AABBBufferArray.points[0] = AABBVertexArray.points[0];
	AABBBufferArray.points[1] = AABBVertexArray.points[3];

	//line 2
	AABBBufferArray.points[2] = AABBVertexArray.points[0];
	AABBBufferArray.points[3] = AABBVertexArray.points[1];

	//line 3
	AABBBufferArray.points[4] = AABBVertexArray.points[1];
	AABBBufferArray.points[5] = AABBVertexArray.points[2];

	//line 4
	AABBBufferArray.points[6] = AABBVertexArray.points[2];
	AABBBufferArray.points[7] = AABBVertexArray.points[3];

	//second quadrant (back)
	//line 5
	AABBBufferArray.points[8] = AABBVertexArray.points[4];
	AABBBufferArray.points[9] = AABBVertexArray.points[5];

	//line 6
	AABBBufferArray.points[10] = AABBVertexArray.points[5];
	AABBBufferArray.points[11] = AABBVertexArray.points[6];

	//line 7
	AABBBufferArray.points[12] = AABBVertexArray.points[6];
	AABBBufferArray.points[13] = AABBVertexArray.points[7];

	//line 8
	AABBBufferArray.points[14] = AABBVertexArray.points[7];
	AABBBufferArray.points[15] = AABBVertexArray.points[4];

	//z lines
	//line 9
	AABBBufferArray.points[16] = AABBVertexArray.points[1];
	AABBBufferArray.points[17] = AABBVertexArray.points[6];

	//line 10
	AABBBufferArray.points[18] = AABBVertexArray.points[2];
	AABBBufferArray.points[19] = AABBVertexArray.points[7];

	//line 11 
	AABBBufferArray.points[20] = AABBVertexArray.points[3];
	AABBBufferArray.points[21] = AABBVertexArray.points[4];

	//line 12
	AABBBufferArray.points[22] = AABBVertexArray.points[0];
	AABBBufferArray.points[23] = AABBVertexArray.points[5];
	

	//pushback points for the lines in the vector that is going to be used in the vertex buffer
	squareVertexArray.push_back(AABBBufferArray);

	D3D11_BUFFER_DESC vertexBufferDesc;
	ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));

	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(AABBVertex);
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA vertexBufferData;
	ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));
	vertexBufferData.pSysMem = &squareVertexArray[0];

	//We store the points in the vertAABBBuffer anhd then use it in the render function to be able to render this
	gDevice->CreateBuffer(&vertexBufferDesc, &vertexBufferData, &vertAABBBuffer);

}

bool Graphics::AABBtoAABB()
{
	//This is the function for collision detection
	//The fucntion compares min and max values of the two AABB's
	//here is the problem, the collsion isn't correct

	if (AABBVertexArray.points[7].x < triVertexArray.points[0].x);
	{
		cout << "no hit" << endl;
		return false;
	}
	
	if (AABBVertexArray.points[0].x > triVertexArray.points[3].x)
	{
		cout << "no hit";
		return false;
	}

	if (AABBVertexArray.points[7].y < triVertexArray.points[0].y)
	{
		cout << "no hit";
		return false;
	}
	if (AABBVertexArray.points[0].y > triVertexArray.points[3].y)
	{
		cout << "no hit";
		return false;
	}

	//if (AABBVertexArray.points[7].z < triVertexArray.points[0].z && AABBVertexArray.points[0].z > triVertexArray.points[3].z) 
	//{
	//	cout << "no hit";
	//	return false;
	//}

	//cout << "hit" << endl;
	return true;

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

	gDeviceContext->Unmap(gConstantBuffer, 0);

	gDeviceContext->VSSetConstantBuffers(0, 1, &gConstantBuffer);
}

bool Graphics::LoadObjModel(wstring filename, ID3D11Buffer** vertBuff, ID3D11Buffer** indexBuff, vector<int>& subsetIndexStart, vector<int>& subsetMaterialArray, vector<SurfaceMaterial>& material, int& subsetCount, bool isRHCoordSys, bool computeNormals)
{
	HRESULT hr = 0;

	wifstream fileIn(filename.c_str());		//Open file
	wstring meshMatLib;						//String to hold our obj material library filename
	wstring filePath;
	filePath = filename.c_str();
	filePath.pop_back(); filePath.pop_back(); filePath.pop_back();
	filePath.push_back('m'); filePath.push_back('t'); filePath.push_back('l');

	//Arrays to store our model's information
	vector<DWORD> indices;
	vector<XMFLOAT3> vertPos;
	vector<XMFLOAT3> vertNorm;
	vector<XMFLOAT2> vertTexCoord;
	vector<wstring> meshMaterials;

	//Vertex definition indices
	vector<int> vertPosIndex;
	vector<int> vertNormIndex;
	vector<int> vertTCIndex;

	//Make sure we have a default if no tex coords or normals are defined
	bool hasTexCoord = false;
	bool hasNorm = false;

	//Temp variables to store into vectors
	wstring meshMaterialsTemp;
	int vertPosIndexTemp;
	int vertNormIndexTemp;
	int vertTCIndexTemp;

	wchar_t checkChar;			//The variable we will use to store one char from file at a time
	wstring face;				//Holds the string containing our face vertices
	int vIndex = 0;				//Keep track of our vertex index count
	int triangleCount = 0;		//Total Triangles
	int totalVerts = 0;
	int meshTriangles = 0;

	//Check to see if file was opened
	if (fileIn)
	{
		while (fileIn)
		{
			checkChar = fileIn.get();	//Get next char
			switch (checkChar)
			{
			case '#':
				checkChar = fileIn.get();
				while (checkChar != '\n')
					checkChar = fileIn.get();
				break;

			case 'v':		//Get Vertex Descriptions
				checkChar = fileIn.get();
				if (checkChar == ' ')	//v - vert position
				{
					float vz, vy, vx;
					fileIn >> vz >> vy >> vx;	//Store the next three types

					if (isRHCoordSys)	//If model is from an RH Coord System
						vertPos.push_back(XMFLOAT3(vx, vy, vz*-1.0f));		//Invert the z axis
					else
						vertPos.push_back(XMFLOAT3(vx, vy, vz));
				}
				if (checkChar == 't')	//vt - vert tex coords
				{
					float vtcu, vtcv;
					fileIn >> vtcu >> vtcv;		//Store next two types

					if (isRHCoordSys)	//If model is from an RH Coord System
						vertTexCoord.push_back(XMFLOAT2(vtcu, 1.0f - vtcv));	//Reverse the "v" axis
					else
						vertTexCoord.push_back(XMFLOAT2(vtcu, vtcv));

					hasTexCoord = true;		//We know the model usese texture coords
				}
				if (checkChar == 'n')	//vn - vert normal
				{
					float vnx, vny, vnz;
					fileIn >> vnx >> vny >> vnz;	//Store next three types

					if (isRHCoordSys)	//If model is from an RH Coord System
						vertNorm.push_back(XMFLOAT3(vnx, vny, vnz*-1.0f));		//Invert the Z axis
					else
						vertNorm.push_back(XMFLOAT3(vnx, vny, vnz));

					hasNorm = true;		//We know the model defines normals
				}
				break;

			case 'g':		//g - defines a group
				checkChar = fileIn.get();
				if (checkChar == ' ')
				{
					subsetIndexStart.push_back(vIndex);			//Start index for this subset
					subsetCount++;
				}
				break;

			case 'f':		//f - defines the faces
				checkChar = fileIn.get();
				if (checkChar == ' ')
				{
					face = L"";
					wstring VertDef;		//Holds one vertex definition at a time
					triangleCount = 0;

					checkChar = fileIn.get();
					while (checkChar != '\n')
					{
						face += checkChar;			//Add the char to our face string
						checkChar = fileIn.get();	//Get the next Character
						if (checkChar == ' ')		//If its a space
							triangleCount++;		//Increase our triangle count
					}
					//Check for space at the end of our face string
					if (face[face.length() - 1] == ' ')
						triangleCount--;		//Each space adds to our triangle count

					triangleCount -= 1;			//Ever vertex in the face AFTER the first two are new faces

					wstringstream ss(face);

					if (face.length() > 0)
					{
						int firstVIndex = 0;
						int lastVIndex = 0;		//Holds the first and last vertice's index

						for (int i = 0; i < 3; i++)
						{
							ss >> VertDef;		//Get vertex definition (vPos/vTexCoord/vNorm)

							wstring vertPart;
							int whichPart = 0;	//(vPos/vTexCoord/vNorm)

												//Parse this string
							for (int j = 0; j < VertDef.length(); j++)
							{
								if (VertDef[j] != '/')		//If there is no divider "/", add a char to our vertPart
									vertPart += VertDef[j];

								//If the current char is a divider "/", or its last character in the string
								if (VertDef[j] == '/' || j == VertDef.length() - 1)
								{
									wistringstream wstringToInt(vertPart);		//Used to convert wstring to int

									if (whichPart == 0)		//If vTexCoord
									{
										wstringToInt >> vertPosIndexTemp;
										vertPosIndexTemp -= 1;			//subtract one since c++ arrays start with 0, and obj start with 1

																		//Check to see if the vert pos was the only thing specified
										if (j == VertDef.length() - 1)
										{
											vertNormIndexTemp = 0;
											vertTCIndexTemp = 0;
										}
									}
									else if (whichPart == 1)		//If vTexCoord
									{
										if (vertPart != L"")		//Check to see if there even is a tex coord
										{
											wstringToInt >> vertTCIndexTemp;
											vertTCIndexTemp -= 1;	//subtract one since c++ arrays start with 0, and obj start with 1
										}
										else		//If there is no tex coord, make a default
											vertTCIndexTemp = 0;

										//If the cur. char is the second to last in the string, then there must  be no normal, so set a default normal
										if (j == VertDef.length() - 1)
											vertNormIndexTemp = 0;
									}
									else if (whichPart == 2)			//If vNorm
									{
										wistringstream wstringToInt(vertPart);

										wstringToInt >> vertNormIndexTemp;
										vertNormIndexTemp -= 1;			//subtract one since c++ arrays start with 0, and obj start with 1
									}

									vertPart = L"";			//Get ready for next vertex part
									whichPart++;			//Move on to next vertex part
								}
							}

							//Check to make sure there is at least one subset
							if (subsetCount == 0)
							{
								subsetIndexStart.push_back(vIndex);			//Start index for this subset
								subsetCount++;
							}

							//Avoid duplicate vertices
							bool vertAlreadyExists = false;
							if (totalVerts >= 3)		//Make sure we at least have one triangle to check
							{
								//Loop through all the verticies
								for (int iCheck = 0; iCheck < totalVerts; iCheck++)
								{
									//If the vertex position and texture coordinate in memory are the same as the vertex position and texture coordinate we just 
									//now got out of the obj file, we will set this faces vertex index to the vertex's index value in memory. This makes sure we don't create duplicate vertices
									if (vertPosIndexTemp == vertPosIndex[iCheck] && !vertAlreadyExists)
									{
										if (vertTCIndexTemp == vertTCIndex[iCheck])
										{
											indices.push_back(iCheck);			//Set index for this vertex
											vertAlreadyExists = true;			//If we've made it here, the vertex already exists
										}
									}
								}
							}
							//If this vertex is not already in our vertex arrays, put it there
							if (!vertAlreadyExists)
							{
								vertPosIndex.push_back(vertPosIndexTemp);
								vertTCIndex.push_back(vertTCIndexTemp);
								vertNormIndex.push_back(vertNormIndexTemp);
								totalVerts++;							//We created a new vertex
								indices.push_back(totalVerts - 1);		//Set index for this vertex
							}

							//If this was the last vertex in the first triangle, we will make sure the next triangle uses this one
							if (i == 2)
							{
								lastVIndex = indices[vIndex];		//The last vertex index of this TRIANGLE
							}
							vIndex++;		//Increment index count
						}

						meshTriangles++;	//One Triangle down

											//If there are more than three vertices in the face definition, we need to make sure we convert the face to triangles. We created our first triangle above, now we will
											//create a new triangle for every new vertex in the face, using the very first vertex of the face, and the last vertex from the triangle before the current triangle
						for (int l = 0; l < triangleCount - 1; l++)		//Loop through the next vertices to create new triangles
						{
							//First vertex of this triangle
							indices.push_back(firstVIndex);				//Set index for this vertex
							vIndex++;

							//Second vertex of this triangle
							indices.push_back(lastVIndex);				//Set index for this vertex
							vIndex++;

							//Get the third vertex for this triangle
							ss >> VertDef;

							wstring vertPart;
							int whichPart = 0;

							//Parse this string
							for (int j = 0; j < VertDef.length(); j++)
							{
								if (VertDef[j] != '/')
									vertPart += VertDef[j];
								if (VertDef[j] == '/' || j == VertDef.length() - 1)
								{
									wistringstream wstringToInt(vertPart);

									if (whichPart == 0)
									{
										wstringToInt >> vertPosIndexTemp;
										vertPosIndexTemp -= 1;

										//Check to see if the vert pos was the only thing specified
										if (j == VertDef.length() - 1)
										{
											vertTCIndexTemp = 0;
											vertNormIndexTemp = 0;
										}
									}
									else if (whichPart == 1)
									{
										if (vertPart != L"")
										{
											wstringToInt >> vertTCIndexTemp;
											vertTCIndexTemp -= 1;
										}
										else
											vertTCIndexTemp = 0;
										if (j == VertDef.length() - 1)
											vertNormIndexTemp = 0;
									}
									else if (whichPart == 2)
									{
										wistringstream wstringToInt(vertPart);

										wstringToInt >> vertNormIndexTemp;
										vertNormIndexTemp -= 1;
									}

									vertPart = L"";
									whichPart++;
								}
							}

							//Check for duplicate vertices
							bool vertAlreadyExists = false;
							if (totalVerts >= 3)			//Make sure we at least have one triangle to check
							{
								for (int iCheck = 0; iCheck < totalVerts; iCheck++)
								{
									if (vertPosIndexTemp == vertPosIndex[iCheck] && !vertAlreadyExists)
									{
										if (vertTCIndexTemp == vertTCIndex[iCheck])
										{
											indices.push_back(iCheck);			//Set index for this vertex
											vertAlreadyExists = true;			//If we've made it here, the vertex already exists
										}
									}
								}
							}
							if (!vertAlreadyExists)
							{
								vertPosIndex.push_back(vertPosIndexTemp);
								vertTCIndex.push_back(vertTCIndexTemp);
								vertNormIndex.push_back(vertNormIndexTemp);
								totalVerts++;							//New vertex created, add to total verts
								indices.push_back(totalVerts - 1);		//Set index for this vertex
							}

							//Set the second vertex for the next triangle to the last vertex we got
							lastVIndex = indices[vIndex];		//The last vertex index of this TRIANGLE

							meshTriangles++;					//New triangle defined
							vIndex++;
						}
					}
				}
				break;

			case 'm':		//mtllib - material library filename
				checkChar = fileIn.get();
				if (checkChar == 't')
				{
					checkChar = fileIn.get();
					if (checkChar == 'l')
					{
						checkChar = fileIn.get();
						if (checkChar == 'l')
						{
							checkChar = fileIn.get();
							if (checkChar == 'i')
							{
								checkChar = fileIn.get();
								if (checkChar == 'b')
								{
									checkChar = fileIn.get();
									if (checkChar == ' ')
									{
										//Store the material libraries filename
										meshMatLib = filePath;
									}
								}
							}
						}
					}
				}
				break;

			case 'u':		//usemtl - which material to use
				checkChar = fileIn.get();
				if (checkChar == 's')
				{
					checkChar = fileIn.get();
					if (checkChar == 'e')
					{
						checkChar = fileIn.get();
						if (checkChar == 'm')
						{
							checkChar = fileIn.get();
							if (checkChar == 't')
							{
								checkChar = fileIn.get();
								if (checkChar == 'l')
								{
									checkChar = fileIn.get();
									if (checkChar == ' ')
									{
										meshMaterialsTemp = L"";		//Make sure this is cleared

										fileIn >> meshMaterialsTemp;	//Get next type

										meshMaterials.push_back(meshMaterialsTemp);
									}
								}
							}
						}
					}
				}
				break;

			default:
				break;
			}
		}
	}
	else			//If we could not open the file
	{
		gSwapChain->SetFullscreenState(false, NULL);		//Make sure we are out of fullscreen

															//create message
		LPCSTR message = "Could not open OBJ file ";

		MessageBox(0, message, "Error", MB_OK);

		return false;
	}

	subsetIndexStart.push_back(vIndex); //There won't be another index start after our last subset, so set it here

										//This makes sure the first subset does not contain '0' indices
	if (subsetIndexStart[1] == 0)
	{
		subsetIndexStart.erase(subsetIndexStart.begin() + 1);
		meshSubsets--;
	}

	//Make sure you have a default for the tex coord and normal
	if (!hasNorm)
		vertNorm.push_back(XMFLOAT3(0.0f, 0.0f, 0.0f));
	if (!hasTexCoord)
		vertTexCoord.push_back(XMFLOAT2(0.0f, 0.0f));

	//Close the obj file, and open the mtl file
	fileIn.close();
	fileIn.open(meshMatLib.c_str());

	wstring lastStringRead;
	int matCount = material.size();		//total materials

	bool kdset = false;

	if (fileIn)
	{
		while (fileIn)
		{
			checkChar = fileIn.get();	//Get next char

			switch (checkChar)
			{
				//Check for comment
			case '#':
				checkChar = fileIn.get();
				while (checkChar != '\n')
					checkChar = fileIn.get();
				break;

				//Set diffuse color
			case 'K':
				checkChar = fileIn.get();
				//Diffuse color
				if (checkChar == 'd')
				{
					checkChar = fileIn.get();

					fileIn >> material[matCount - 1].difColor.x;
					fileIn >> material[matCount - 1].difColor.y;
					fileIn >> material[matCount - 1].difColor.z;

					kdset = true;
				}

				//Ambient color
				if (checkChar == 'a')
				{
					checkChar = fileIn.get();
					if (!kdset)
					{
						fileIn >> material[matCount - 1].difColor.x;
						fileIn >> material[matCount - 1].difColor.y;
						fileIn >> material[matCount - 1].difColor.z;
					}
				}
				break;

				//Check for transparency
			case 'T':
				checkChar = fileIn.get();
				if (checkChar == ' ')
				{
					checkChar = fileIn.get();
					float Transparency;
					fileIn >> Transparency;

					material[matCount - 1].difColor.w = Transparency;

					if (Transparency > 0.0f)
						material[matCount - 1].transparent = true;
				}
				break;

				//Some obj have d for transparency
			case 'd':
				checkChar = fileIn.get();
				if (checkChar == ' ')
				{
					checkChar = fileIn.get();
					float Transparency;
					fileIn >> Transparency;

					material[matCount - 1].difColor.w = Transparency;

					if (Transparency > 0.0f)
						material[matCount - 1].transparent = true;
				}
				break;

				//Get the diffuse map (texture)
			case 'm':
				checkChar = fileIn.get();
				if (checkChar == 'a')
				{
					checkChar = fileIn.get();
					if (checkChar == 'p')
					{
						checkChar = fileIn.get();
						if (checkChar == '_')
						{
							checkChar = fileIn.get();
							if (checkChar == 'K')
							{
								checkChar = fileIn.get();
								if (checkChar == 'd')
								{
									wstring fileNamePath;

									fileIn.get();		//Removes whitespace between map_Kd an file

									bool texFilePathEnd = false;
									while (!texFilePathEnd)
									{
										checkChar = fileIn.get();

										fileNamePath += checkChar;

										if (checkChar == '.')
										{
											for (int i = 0; i < 3; i++)
												fileNamePath += fileIn.get();

											texFilePathEnd = true;
										}
									}
									//Has texture already been loaded
									bool alreadyLoaded = false;
									for (int i = 0; i < textureNameArray.size(); i++)
									{
										if (fileNamePath == textureNameArray[i])
										{
											alreadyLoaded = true;
											material[matCount - 1].texArrayIndex = i;
											material[matCount - 1].hasTexture = true;
										}
									}
									//load texture
									if (!alreadyLoaded)
									{
										ID3D11ShaderResourceView* tempMeshSRV;
										hr = CreateWICTextureFromFile(gDevice, fileNamePath.c_str(), NULL, &tempMeshSRV, 0);
										if (SUCCEEDED(hr))
										{
											textureNameArray.push_back(fileNamePath.c_str());
											material[matCount - 1].texArrayIndex = meshSRV.size();
											meshSRV.push_back(tempMeshSRV);
											material[matCount - 1].hasTexture = true;
										}
									}
								}
							}
							//map_d - alpha map
							else if (checkChar == 'd')
							{
								material[matCount - 1].transparent = true;
							}
						}
					}
				}
				break;

			case 'n':		//newmtl - declare new material
				checkChar = fileIn.get();
				if (checkChar == 'e')
				{
					checkChar = fileIn.get();
					if (checkChar == 'w')
					{
						checkChar = fileIn.get();
						if (checkChar == 'm')
						{
							checkChar = fileIn.get();
							if (checkChar == 't')
							{
								checkChar = fileIn.get();
								if (checkChar == 'l')
								{
									checkChar = fileIn.get();
									if (checkChar == ' ')
									{
										//New material
										SurfaceMaterial tempMat;
										material.push_back(tempMat);
										fileIn >> material[matCount].matName;
										material[matCount].transparent = false;
										material[matCount].hasTexture = false;
										material[matCount].texArrayIndex = 0;
										matCount++;
										kdset = false;
									}
								}
							}
						}
					}
				}
				break;

			default:
				break;
			}
		}
	}
	else
	{
		gSwapChain->SetFullscreenState(false, NULL);		//Make sure we are out of fullscreen

		LPCSTR message = "Could not open MTL file ";

		MessageBox(0, message, "Error", MB_OK);

		return false;
	}
	//Sets the subsets material to the index value of the its material in our material array
	for (int i = 0; i < meshSubsets; i++)
	{
		bool hasMat = false;
		for (int j = 0; j < material.size(); j++)
		{
			if (meshMaterials[i] == material[j].matName)
			{
				subsetMaterialArray.push_back(j);
				hasMat = true;
			}
		}
		if (!hasMat)
			subsetMaterialArray.push_back(0); //Use first material in array
	}

	vector<Vertex> vertices;
	Vertex tempVert;

	//Create our vertices using the information we got from the file and store them in a vector
	for (int i = 0; i < totalVerts; i++)
	{
		tempVert.pos = vertPos[vertPosIndex[i]];
		tempVert.normal = vertNorm[vertNormIndex[i]];
		tempVert.texCoord = vertTexCoord[vertTCIndex[i]];

		vertices.push_back(tempVert);
		vertexMeshSize.push_back(tempVert);
	}
	//************COMPUTE NORMAL*********************
	if (computeNormals)
	{
		vector<XMFLOAT3> tempNormal;

		//normalized and unnormalized normals
		XMFLOAT3 unnormalized = XMFLOAT3(0.0f, 0.0f, 0.0f);

		//Used to get vectors (sides) from the position of the verts
		float vecX, vecY, vecZ;

		//Two edges of our triangle
		XMVECTOR edge1 = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
		XMVECTOR edge2 = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);

		//Compute face normals
		for (int i = 0; i < meshTriangles; i++)
		{
			//Get the vector describing one edge of our triangle (edge 0, 2)
			vecX = vertices[indices[(i * 3)]].pos.x - vertices[indices[(i * 3) + 2]].pos.x;
			vecY = vertices[indices[(i * 3)]].pos.y - vertices[indices[(i * 3) + 2]].pos.y;
			vecZ = vertices[indices[(i * 3)]].pos.z - vertices[indices[(i * 3) + 2]].pos.z;
			edge1 = XMVectorSet(vecX, vecY, vecZ, 0.0f);

			//(edge 2, 1)
			vecX = vertices[indices[(i * 3) + 2]].pos.x - vertices[indices[(i * 3) + 1]].pos.x;
			vecY = vertices[indices[(i * 3) + 2]].pos.y - vertices[indices[(i * 3) + 1]].pos.y;
			vecZ = vertices[indices[(i * 3) + 2]].pos.z - vertices[indices[(i * 3) + 1]].pos.z;
			edge2 = XMVectorSet(vecX, vecY, vecZ, 0.0f);

			//Cross product
			XMStoreFloat3(&unnormalized, XMVector3Cross(edge1, edge2));
			tempNormal.push_back(unnormalized);
		}

		//Compute vertex normals
		XMVECTOR normalSum = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
		float facesUsing = 0;
		float tX;
		float tY;
		float tZ;

		//Go through each vertex
		for (int i = 0; i < totalVerts; i++)
		{
			for (int j = 0; j < meshTriangles; j++)
			{
				if (indices[j * 3] == i || indices[(j * 3) + 1] == i || indices[(j * 3) + 2] == i)
				{
					tX = XMVectorGetX(normalSum) + tempNormal[j].x;
					tY = XMVectorGetY(normalSum) + tempNormal[j].y;
					tZ = XMVectorGetZ(normalSum) + tempNormal[j].z;

					normalSum = XMVectorSet(tX, tY, tZ, 0.0f);
					facesUsing++;
				}
			}
			//Get the actual normal by dividing the normalSum by the number of faces sharing the vertex
			normalSum = normalSum / facesUsing;

			//Normalize
			normalSum = XMVector3Normalize(normalSum);

			//Store the normal in our current vertex
			vertices[i].normal.x = XMVectorGetX(normalSum);
			vertices[i].normal.y = XMVectorGetY(normalSum);
			vertices[i].normal.z = XMVectorGetZ(normalSum);

			//Clear normalSum and facesUsing for next vertex
			normalSum = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
			facesUsing = 0;
		}
	}

	//Create index buffer
	D3D11_BUFFER_DESC indexBufferDesc;
	ZeroMemory(&indexBufferDesc, sizeof(indexBufferDesc));

	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(DWORD) * meshTriangles * 3;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA iinitData;

	iinitData.pSysMem = &indices[0];
	hr = gDevice->CreateBuffer(&indexBufferDesc, &iinitData, indexBuff);

	//Create Vertex Buffer
	D3D11_BUFFER_DESC vertexBufferDesc;
	ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));

	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(Vertex) * totalVerts;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA vertexBufferData;
	ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));

	vertexBufferData.pSysMem = &vertices[0];
	hr = gDevice->CreateBuffer(&vertexBufferDesc, &vertexBufferData, vertBuff);

	return true;
}