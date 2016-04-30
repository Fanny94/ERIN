#include "ObjectPool.h"

ObjectPool::ObjectPool()
{
	firstAvailable = &bullets[0];

	for (int i = 0; i < poolSize - 1; i++)
	{
		bullets[i].setNext(&bullets[i + 1]);
	}

	bullets[poolSize - 1].setNext(NULL);
}

ObjectPool::~ObjectPool()
{
}

void ObjectPool::createb(float x, float y, int lifeTime)
{
	assert(firstAvailable != NULL);

	Bullet* newBullet = firstAvailable;
	firstAvailable = newBullet->getNext();

	newBullet->iniBullet(x, y, lifeTime);
}

void ObjectPool::fire()
{
	if (fbull.canFire = true)
	{
		createb(x, y, lifeTime);
		fbull.countdown = 60;
	}
}