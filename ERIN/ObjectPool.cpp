#include "ObjectPool.h"



ObjectPool::ObjectPool()
{
	//firstOne = &bullets[0];


}


ObjectPool::~ObjectPool()
{
}

void ObjectPool::createb(float x, float y, int lifeTime)
{
	for (int i = 0; i < poolSize; i++)
	{
		if (!bullets[i].getInUse())
		{
			bullets[i].iniBullet(x, y, lifeTime);
			return;
		}
	}
}

void ObjectPool::iniErry()
{
	createb(x, y, timeLeft);
}
