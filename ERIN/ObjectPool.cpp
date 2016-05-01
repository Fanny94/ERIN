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

void ObjectPool::createb(float x, float y, float z, int lifeTime)
{
	assert(firstAvailable != NULL);

	Bullet* newBullet = firstAvailable;
	firstAvailable = newBullet->getNext();

	newBullet->iniBullet(x, y, z, lifeTime);
}

void ObjectPool::fire()
{
	createb(x, y, z, lifeTime);
	fbull.countdown = 60;
	if (fbull.canFire = true)
	{
		for (int i = 0; i < poolSize; i++)
		{
			graph->RendPlayer(*ptrBull[i]->bulletMatrix);
		}
	}
}