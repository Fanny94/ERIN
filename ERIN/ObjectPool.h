#pragma once
#include "Bullet.h"
//#include <ctime>
//#include <time.h>

class ObjectPool
{
public:
	ObjectPool();
	~ObjectPool();
	void createb(float x, float y, int lifeTime);
	void fire();
private:
	float x, y;
	int lifeTime;
	Bullet* firstAvailable;
	static const int poolSize = 100;
	Bullet bullets[poolSize];
	Bullet fbull;
};