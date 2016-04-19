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

	this->input = new Input(GamePadIndex_One);

	// test triangle in gameobject
	this->triangle = new TriangleVertex[3];
<<<<<<< HEAD
	this->axisAllignedBox = new AABBBox;

=======
	
>>>>>>> refs/remotes/origin/master
	this->triangle[0] = { 0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, };
	this->triangle[1] = { 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, };
	this->triangle[2] = { -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f };

<<<<<<< HEAD
	this->axisAllignedBox->min = XMFLOAT3(FLT_MAX, FLT_MAX, FLT_MAX);
	this->axisAllignedBox->max = XMFLOAT3(-FLT_MAX, -FLT_MAX, -FLT_MAX);
=======
	this->objectMatrix = new Matrix();
>>>>>>> refs/remotes/origin/master
}

GameObject::~GameObject()
{
	delete this->input;
	delete this->triangle;
<<<<<<< HEAD
	delete this->axisAllignedBox;
=======
	delete this->objectMatrix;
}

void GameObject::update()
{
	//*this->objectMatrix = XMMatrixRotationZ(XMConvertToRadians(0.0f)) * XMMatrixTranslation(x, y, z) * XMMatrixScaling(0.0f, 0.0f, 0.0f);
	*this->objectMatrix = XMMatrixTranslation(x, y, z);
>>>>>>> refs/remotes/origin/master
}

