#pragma once
#include "Bullet.h"
#include "Graphics.h"
//#include <ctime>
//#include <time.h>

class ObjectPool
{
public:
	ObjectPool();
	~ObjectPool();
	void createb(float x, float y, float z, int lifeTime);
	void fire();
private:
	Graphics* graph;
	float x, y, z;
	int lifeTime;
	Bullet* firstAvailable;
	static const int poolSize = 100;
	Bullet bullets[poolSize];
	Bullet fbull;
	Bullet** ptrBull;
};