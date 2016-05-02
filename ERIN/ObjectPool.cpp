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

/*void ObjectPool::createb(float x, float y, float z, int lifeTime, bool inUse)
{
	//assert(firstAvailable != NULL);

	for (int i = 0; i < poolSize; i++)
	{
		if (!bullets[i].getInUse())
		{
			bullets[i].iniBullet(x, y, z, lifeTime, inUse);
			bullets[i].inUse = true;
		}
	}
	
	/*Bullet* newBullet = firstAvailable;
	firstAvailable = newBullet->getNext();

	newBullet->iniBullet(x, y, z, lifeTime);*/
//}

void ObjectPool::fire()
{
	
	/*if (fbull.lastFire == 0)
	{
		Bullet* newBullet = firstAvailable;
		firstAvailable = newBullet->getNext();

		newBullet->iniBullet(0, 0, 0, fbull.timeLeft);
		fbull.lastFire = 100;
	}*/
	//if (fbull.canFire=true)
	//{
		for (int i = 0; i < poolSize; i++)
		{
			if (!bullets[i].getInUse())
			{
				bullets[i].iniBullet(fbull.state.alive.x, fbull.state.alive.y, fbull.state.alive.z, fbull.timeLeft);//(bullets[i].bulletPos->x, bullets[i].bulletPos->y, bullets[i].bulletPos->z, fbull.timeLeft);
				bullets[i].inUse = true;
				//fbull.canFire = false;
				//animate();
				//pfbull.lastFire = 200;
				return;
			}
		}
	//}
}