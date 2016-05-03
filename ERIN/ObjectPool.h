#pragma once
#include "Bullet.h"


class ObjectPool
{
public:
	ObjectPool();
	~ObjectPool();
	void fire();
	int getSize() { return this->poolSize; };
	static const int poolSize = 100;
	Bullet bullets[poolSize];
	void animate();
	float SPosx;
	float SPosy;
	float SHead;
private:
	float x, y, z;
	int lifeTime;
	Bullet* firstAvailable;
	Bullet fbull;
	Bullet** ptrBull;
};