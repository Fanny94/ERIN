#include "ObjectPool.h"

ObjectPool::ObjectPool()
{
	// Bullets
	firstAvailable = &bullets[0];

	for (int i = 0; i < this->b_poolSize - 1; i++)
	{
		bullets[i].setNext(&bullets[i + 1]);
	}

	bullets[this->b_poolSize - 1].setNext(NULL);

	// Enemies
	first = &enemies[0];

	for (int i = 0; i < this->e_poolSize; i++)
	{
		enemies[i].setObjectID(100 + i);
		enemies[i].setObjectName("enemy" + i);

		enemies[i].setInUse(false);

		// speed
		float LO = 0.07f, HI = 0.15f, lO = 0.0006f, hI = 0.0009f;
		float Random = LO + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (HI - LO)));
		enemies[i].setMaxSpeed(Random);

		float Ran = lO + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (hI - lO)));
		enemies[i].setAcceleration(Ran);

		enemies[i].setNext(&enemies[i + 1]);
	}

	enemies[this->e_poolSize - 1].setNext(NULL);
}

ObjectPool::~ObjectPool()
{
}

void ObjectPool::ResetBullet()
{
	for (int i = 0; i < this->b_poolSize; i++)
	{
		if (bullets[i].getInUse())
		{
			this->bullets[i].state.alive.x = 0.0f;
			this->bullets[i].state.alive.y = 0.0f;
			this->bullets[i].state.alive.z = 0.0f;

			this->bullets[i].timeLeft = 0;
			//this->speed = 0.0f;

			delete this->fbull.bulletMatrix;
			this->fbull.bulletMatrix = new Matrix();
		}
	}
}


void ObjectPool::handler()
{
	for (int i = 0; i < b_poolSize; i++)
	{
		if (!bullets[i].getInUse())
		{
			bullets[i].setNext(firstAvailable);
			firstAvailable = &bullets[i];
		}
	}
}

void ObjectPool::fire(float x, float y, double heading)
{
	Bullet* newBullet = firstAvailable;
	firstAvailable = newBullet->getNext();
	
	newBullet->iniBullet(x, y, 0.0f, fbull.timeLeft);
	newBullet->bullet_heading = heading;
	newBullet->setInUse(true);
	handler();
	return;
}

void ObjectPool::bulletupdateCooldown(double bdt)
{
	if (this->bcooldown <= this->bcurrentTime)
	{
		this->bcurrentTime = 0.0f;
		this->bReady = true;
	}
	else
	{
		this->bcurrentTime += bdt;
	}
}

void ObjectPool::createEnemy(float x, float y, float z)
{
	for (int i = 0; i < this->e_poolSize; i++)
	{
		if (!enemies[i].getInUse())
		{
			enemies[i].setObjectPosX(x);
			enemies[i].setObjectPosY(y);
			enemies[i].setObjectPosZ(z);
			enemies[i].setInUse(true);
			return;
		}
	}
}