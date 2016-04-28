#include "Player.h"

Player::Player()
	: name("noName"),
	x(0.0f), y(0.0f), z(0.0f)
{
}

Player::Player(string name, float x, float y, float z)
{
	this->name = name;
	this->x = x;
	this->y = y;
	this->z = z;

	this->maximumSpeed = 0.1f;
	this->currentSpeed = 0.0f;

	this->speed = 0.0f;
	this->acceleration = 0.0005f;

	this->input = new Input(GamePadIndex_One);

	this->triangle = new TriangleVertex[3];

	this->triangle[0] = { 0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, };
	this->triangle[1] = { 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, };
	this->triangle[2] = { -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f };

	this->objectMatrix = new Matrix();

	//this->axisAllignedBox = new AABBBox;
	/*this->axisAllignedBox->min = XMFLOAT3(FLT_MAX, FLT_MAX, FLT_MAX);
	this->axisAllignedBox->max = XMFLOAT3(-FLT_MAX, -FLT_MAX, -FLT_MAX);*/

	this->pos = new Position{ this->x, this->y, this->z };
}

Player::~Player()
{
	delete this->input;
	delete this->triangle;
	delete this->objectMatrix;
	//delete this->axisAllignedBox;
	delete this->pos;
}


void Player::playerInput()
{
	if (input->isConnected())
	{
		this->thumbLeftX = input->State._left_thumbstick.x;
		this->thumbLeftY = input->State._left_thumbstick.y;

		if ((thumbLeftX && thumbLeftY) == 0)
		{
			this->accelerating = false;
		}
		else
		{
			this->accelerating = true;
		}
	}
}

void Player::update(double dt)
{
	this->pos->x = this->x;
	this->pos->y = this->y;
	this->pos->z = this->z;

	if (!accelerating)
	{
		// deacceleration
		if (this->thumbLeftX == 0)
		{
			velocityX *= 0.8f;
		}
		if (this->thumbLeftY == 0)
		{
			velocityY *= 0.8f;
		}
	}
	else
	{
		// Speed += ((MoveDirection * MaximumSpeed) - Speed) * AccelerationFactor

		velocityX += ((thumbLeftX * maximumSpeed) - velocityX) * abs(thumbLeftX);
		velocityY += ((thumbLeftY * maximumSpeed) - velocityY) * abs(thumbLeftY);
	}

	if ((thumbLeftX && thumbLeftY) != 0)
	{
		plannedHeading = XMConvertToDegrees(atan2f(thumbLeftX, thumbLeftY));
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
void Player::computeTurn(double dt)
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

void Player::turnTo(double newHeading)
{
	plannedHeading = newHeading;
}
double Player::getVx()
{
	return r_speed * acos(heading * M_PI / 180);
}
double Player::getVy()
{
	return r_speed * asin(heading * M_PI / 180);
}