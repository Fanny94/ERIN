#pragma once
#include "Bullet.h"


class ObjectPool
{
public:
	ObjectPool();
	~ObjectPool();
	void createb(float x, float y, int lifeTime);
	void iniErry();
	
private:
	int timeLeft; //How long a bullet will last
	float x, y;
	static const int poolSize = 100;
	Bullet bullets[poolSize];
};

