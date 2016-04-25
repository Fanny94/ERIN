#include "GameObject.h"

GameObject::GameObject()
	: name("noName"),
	x(0.0f), y(0.0f), z(0.0f)
{
}

GameObject::GameObject(string name, float x, float y, float z)
{
	this->name = name;
	this->x = x;
	this->y = y;
	this->z = z;

	this->maximumSpeed = 0.1f;
	this->currentSpeed = 0.0f;

	this->speed = 0.0f;
	this->acceleration = 0.0005f;

	// test triangle in gameobject
	this->triangle = new TriangleVertex[3];

	this->triangle[0] = { 0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, };
	this->triangle[1] = { 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, };
	this->triangle[2] = { -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f };

	this->objectMatrix = new Matrix();

	// collision
	this->axisAllignedBox = new AABBBox;
	this->axisAllignedBox->min = XMFLOAT3(FLT_MAX, FLT_MAX, FLT_MAX);
	this->axisAllignedBox->max = XMFLOAT3(-FLT_MAX, -FLT_MAX, -FLT_MAX);
}

GameObject::~GameObject()
{
	delete this->triangle;
	delete this->axisAllignedBox;
	delete this->objectMatrix;
}

void GameObject::behavior()
{
}

void GameObject::update(double deltaTimeMs)
{
	//if (!accelerating)
	//{
	//	// deacceleration
	//	if (this->thumbLeftX == 0)
	//	{
	//		velocityX *= 0.8f;
	//	}
	//	if (this->thumbLeftY == 0)
	//	{
	//		velocityY *= 0.8f;
	//	}
	//}
	//else
	//{
	//	// Speed += ((MoveDirection * MaximumSpeed) - Speed) * AccelerationFactor

	//	velocityX += ((thumbLeftX * maximumSpeed) - velocityX) * abs(thumbLeftX);
	//	velocityY += ((thumbLeftY * maximumSpeed) - velocityY) * abs(thumbLeftY);
	//}
	//
	//x = x + velocityX;
	//y = y + velocityY;

	//*this->objectMatrix = XMMatrixRotationZ(XMConvertToRadians(0.0f)) * XMMatrixTranslation(x, y, z) * XMMatrixScaling(0.0f, 0.0f, 0.0f);
	*this->objectMatrix = XMMatrixTranslation(x, y, z);
}

