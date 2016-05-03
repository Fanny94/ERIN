#ifndef OBJECTPOOL_H
#define OBJECTPOOL_H

#include "Bullet.h"
#include "GameObject.h"

class ObjectPool
{
public:
	ObjectPool();
	~ObjectPool();

	// Bullets
	void fire();
	int getBulletPoolSize() { return this->b_poolSize; };
	static const int b_poolSize = 100;
	Bullet bullets[b_poolSize];

	// Enemies
	void createEnemy(float x, float y, float z);
	int getEnemyPoolSize() { return this->e_poolSize; };
	static const int e_poolSize = 20;
	GameObject enemies[e_poolSize];

	int getSize() { return this->poolSize; };
	static const int poolSize = 100;
	Bullet bullets[poolSize];
	void animate();
	float SPosx;
	float SPosy;
	float SHead;
private:
	// Bullets
	int lifeTime;
	Bullet* firstAvailable;
	Bullet fbull;
	Bullet** ptrBull;

	// Enemies
	GameObject* first;
	GameObject fenemy;
	GameObject** ptrEnemy;

};
#endif
