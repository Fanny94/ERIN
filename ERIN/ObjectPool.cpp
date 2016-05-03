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

void ObjectPool::animate()
{

	for (int i = 0; i < poolSize; i++)
	{
		if (bullets[i].getInUse())
		{
			bullets[i].setNext(firstAvailable);
			firstAvailable = &bullets[i];
		}
	}
}

void ObjectPool::fire()
{
		for (int i = 0; i < poolSize; i++)
		{
			if (!bullets[i].getInUse())
			{
				bullets[i].iniBullet(SPosx, SPosy, fbull.state.alive.z, fbull.timeLeft);
				fbull.bullet_heading = SHead;
				bullets[i].inUse = true;
				return;
			}
		}
}