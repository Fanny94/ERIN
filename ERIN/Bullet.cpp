#include "Bullet.h"


Bullet::Bullet()
{
}


Bullet::~Bullet()
{
}

void Bullet::update()
{
	timeLeft --;

	if (timeLeft == 0)
	{
		//remove the bullet
	}
}

void Bullet::iniBullet(float X, float Y, int lifeTime)
{
	x = X;
	y = Y;
	timeLeft = lifeTime;
}
