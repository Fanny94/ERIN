#include "Bullet.h"

Bullet::Bullet()
{
	this->bulletMatrix = new Matrix();
	this->bulletShadowMatrix = new Matrix();
}

Bullet::~Bullet()
{
	delete this->bulletMatrix;
	delete this->bulletShadowMatrix;
}

void Bullet::update()
{
	timeLeft--;

	if (timeLeft <= 0)
	{
		inUse = false;
		state.alive.x = 0;
		state.alive.y = 0;
		state.alive.z = 0;
		timeLeft = 0;
	}

	float radians = XMConvertToRadians((float)bullet_heading);
	float directionX = (float)sin(radians);
	float directionY = (float)cos(radians);

	state.alive.Velx += ((directionX * this->maxspd) - state.alive.Velx) * abs(1.0f);
	state.alive.Vely += ((directionY * this->maxspd) - state.alive.Vely) * abs(1.0f);

	state.alive.x = state.alive.x + state.alive.Velx;
	state.alive.y = state.alive.y + state.alive.Vely;

	// bullet matrix
	*this->bulletMatrix = XMMatrixScaling(0.25f, 0.25f, 0.25f)
		* XMMatrixRotationZ(XMConvertToRadians((float)-bullet_heading))
		* XMMatrixTranslation(this->state.alive.x, this->state.alive.y, this->state.alive.z);

	// bullet shadow matrix
	*this->bulletShadowMatrix = XMMatrixScaling(0.25f, 0.25f, 0.25f)
		* XMMatrixRotationZ(XMConvertToRadians((float)-bullet_heading))
		* XMMatrixTranslation(this->state.alive.x * 1.03, this->state.alive.y * 1.03, this->state.alive.z + 0.45);
}

void Bullet::iniBullet(float X, float Y, float Z, int lifeTime)
{
	state.alive.x = X;
	state.alive.y = Y;
	state.alive.z = Z;
	timeLeft = lifeTime;
}