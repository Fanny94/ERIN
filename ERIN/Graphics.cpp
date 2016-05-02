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

	/*vertAABBBuffer->Release();
	AABBLayout->Release();
	AABBVertexShader->Release();
	AABBPixelShader->Release();*/

	/*triangleAABBVertexBuffer->Release();*/

	gDepthView->Release();
	gDepthStencilView->Release();

	gConstantBuffer->Release();

	customFormatBuffer->Release();
	this->customFormatBuffer = nullptr;

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


void Graphics::RenderCustom(Mesh mesh, Matrix transform)
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

	D3D11_MAPPED_SUBRESOURCE mappedCF;
	hr = gDeviceContext->Map(customFormatBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedCF);
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

	for (int i = 0; i < mesh.MeshCount; i++)
	{
		gDeviceContext->IASetVertexBuffers(0, 1, &customVertBuff, &meshVertexSize, &offset);
		gDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		CustomUpdateBuffer(transform);

		gDeviceContext->PSSetConstantBuffers(0, 1, &customFormatBuffer);

		gDeviceContext->Draw(mesh.mesh.at(i).vertex.size(), 0);
	}
	customVertBuff->Release();
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

	CustomUpdateBuffer(transform);

	gDeviceContext->Draw(3, 0);
	/*
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

	gDeviceContext->Draw(3, 0);*/
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

	D3D11_BUFFER_DESC cCFBuffer;
	ZeroMemory(&cCFBuffer, sizeof(cCFBuffer));
	cCFBuffer.Usage = D3D11_USAGE_DYNAMIC;
	cCFBuffer.ByteWidth = sizeof(CustomFormat);
	cCFBuffer.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cCFBuffer.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cCFBuffer.MiscFlags = 0;

	gDevice->CreateBuffer(&cCFBuffer, NULL, &customFormatBuffer);
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

void Graphics::CreateSquareAABBBox(Mesh mesh)
{
	//This function defines an AABB box for the cube with a min and a max value

		//go through each vertex of the mesh
	for (int i = 0; i < mesh.mesh.at(0).VertexCount; i++)
	{

		//left bottom corner (front)
		//if vertex position x is smaller than the AABB box's min value
		//the new min value == that vertex position in x
		if (mesh.mesh.at(0).vertex.at(i).pos[0] < axisAllignedBox.min.x)
		{
			axisAllignedBox.min.x = mesh.mesh.at(0).vertex.at(i).pos[0];
		}

		//the new min value == that vertex position in y
		if (mesh.mesh.at(0).vertex.at(i).pos[1] < axisAllignedBox.min.y)
		{
			axisAllignedBox.min.y = mesh.mesh.at(0).vertex.at(i).pos[1];
		}

		//the new min value == that vertex position in z
		if (mesh.mesh.at(0).vertex.at(i).pos[2] < axisAllignedBox.min.z)
		{
			axisAllignedBox.min.z = mesh.mesh.at(0).vertex.at(i).pos[2];
		}

		//right upper corner (back)
		//the new max value == that vertex position in x
		if (mesh.mesh.at(0).vertex.at(i).pos[0] > axisAllignedBox.max.x)
		{
			axisAllignedBox.max.x = mesh.mesh.at(0).vertex.at(i).pos[0];
		}

		//the new max value == that vertex position in y
		if (mesh.mesh.at(0).vertex.at(i).pos[1] > axisAllignedBox.max.y)
		{
			axisAllignedBox.max.y = mesh.mesh.at(0).vertex.at(i).pos[1];
		}

		//the new max value == that vertex position in z
		if (mesh.mesh.at(0).vertex.at(i).pos[2] > axisAllignedBox.max.z)
		{
			axisAllignedBox.max.z = mesh.mesh.at(0).vertex.at(i).pos[2];
		}

		//points == 8 points that later will represent the 8 corners of the AABB cube
		//this is min and max of the mesch
		AABBVertexArray.points[0] = axisAllignedBox.min;
		AABBVertexArray.points[7] = axisAllignedBox.max;
	}
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
	AABBVertexArray.points[4].y = AABBVertexArray.points[3].y;
	AABBVertexArray.points[4].z = AABBVertexArray.points[7].z;
	
	//Left bottom corner (back)
	AABBVertexArray.points[5].x = AABBVertexArray.points[0].x;
	AABBVertexArray.points[5].y = AABBVertexArray.points[0].y;
	AABBVertexArray.points[5].z = AABBVertexArray.points[4].z;

	//Left upper corner (back)
	AABBVertexArray.points[6].x = AABBVertexArray.points[0].x;
	AABBVertexArray.points[6].y = AABBVertexArray.points[7].y;
	AABBVertexArray.points[6].z = AABBVertexArray.points[7].z;


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
void Graphics::RendAABB(Matrix transform)
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