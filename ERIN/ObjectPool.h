#pragma once
#include "Bullet.h"
//#include <ctime>
//#include <time.h>

class ObjectPool
{
public:
	ObjectPool();
	~ObjectPool();
	void createb(float x, float y, float z, int lifeTime);
	void fire();
	int getSize() { return this->poolSize; };
	static const int poolSize = 100;
	Bullet bullets[poolSize];
	void animate();
private:
	float x, y, z;
	int lifeTime;
	Bullet* firstAvailable;
	Bullet fbull;
	Bullet** ptrBull;
};