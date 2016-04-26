#include "GameObject.h"

GameObject::GameObject()
	: name("noName"),
	x(0.0f), y(0.0f), z(0.0f)
{
}

GameObject::GameObject(string name, float x, float y, float z, bool doHaveBehavior)
{
	this->name = name;
	this->x = x;
	this->y = y;
	this->z = z;

	this->maximumSpeed = 0.05f;
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

	// behavoir
	if (doHaveBehavior == true)
	{
		this->behavior = new Behavior(Patrol);
	}

	this->pos = new Position{ this->x, this->y, this->z };
}

GameObject::~GameObject()
{
	delete this->triangle;
	delete this->axisAllignedBox;
	delete this->objectMatrix;
	delete this->pos;

	if (this->behavior)
	{
		delete this->behavior;
	}
}

void GameObject::updateBehavior(Position player)
{
	if (this->behavior != nullptr)
	{
		Position thisEnemy = { this->x, this->y, this->z };
		this->behavior->update(player, thisEnemy);
	}

	float radians = XMConvertToRadians((float)heading);
	this->directionX = (float)sin(radians);
	this->directionY = (float)cos(radians);

	/*if (directionX < 0)
	{
		directionX = 0;
	}
	if (directionY < 0)
	{
		directionY = 0;
	}*/
}

void GameObject::update(double dt)
{
	this->pos->x = this->x;
	this->pos->y = this->y;
	this->pos->z = this->z;

	if (this->behavior->getBehavior() == Follow)
	{
		this->accelerating = true;
	}
	else
	{
		this->accelerating = false;
	}
	
	if (!accelerating)
	{
		// deacceleration
		velocityX *= 0.8f;
		velocityY *= 0.8f;
	}
	else
	{
		// Speed += ((MoveDirection * MaximumSpeed) - Speed) * AccelerationFactor
		velocityX += ((directionX * maximumSpeed) - velocityX) * abs(1.0f);
		velocityY += ((directionY * maximumSpeed) - velocityY) * abs(1.0f);

		plannedHeading = this->behavior->getHeading(); // XMConvertToDegrees(atan2f(thumbLeftX, thumbLeftY));
	}

	x = x + velocityX;
	y = y + velocityY;

	// rotation
	r_x += dt * getVx();
	r_y += dt * getVy();
	if (heading != plannedHeading)
	{
		computeTurn(dt);
	}

	*this->objectMatrix = XMMatrixRotationZ(XMConvertToRadians((float)-heading)) * XMMatrixTranslation(x, y, z) * XMMatrixScaling(1.0f, 1.0f, 1.0f);
}
void GameObject::computeTurn(double dt)
{
	double dh = plannedHeading - heading;
	if (dh < -180)
		dh += 360;
	if (dh > 180)
		dh -= 360;
	if (abs(dh) < turnRate * dt)
		heading = plannedHeading;
	else
	{
		int dir = 1;
		if (dh < 0)
			dir = -1;
		heading += turnRate * dt * dir;
	}
}

void GameObject::turnTo(double newHeading)
{
	plannedHeading = newHeading;
}
double GameObject::getVx()
{
	return r_speed * acos(heading * M_PI / 180);
}
double GameObject::getVy()
{
	return r_speed * asin(heading * M_PI / 180);
}