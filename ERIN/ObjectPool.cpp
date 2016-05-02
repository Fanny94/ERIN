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

void ObjectPool::createb(float x, float y, float z, int lifeTime)
{
	//assert(firstAvailable != NULL);

	for (int i = 0; i < poolSize; i++)
	{
		if (!bullets[i].getInUse())
		{
			bullets[i].iniBullet(x, y, z, lifeTime);
			bullets[i].inUse = true;
		}
	}
	
	/*Bullet* newBullet = firstAvailable;
	firstAvailable = newBullet->getNext();

	newBullet->iniBullet(x, y, z, lifeTime);*/
}

void ObjectPool::fire()
{
	if (fbull.canFire = true)
	{
		for (int i = 0; i < poolSize; i++)
		{
			createb(0, 0, 0, lifeTime);
			//graph->RendPlayer(*ptrBull[i]->bulletMatrix);
		}
	}
}