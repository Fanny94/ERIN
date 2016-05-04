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
	void fire(float x, float y, double heading);
	int getBulletPoolSize() { return this->b_poolSize; };
	static const int b_poolSize = 100;
	Bullet bullets[b_poolSize];
	float SPosx;
	float SPosy;
	float SHead;
	bool getCooldown() { return this->bReady; };
	void setCooldown(bool bReady) { this->bReady = bReady; };
	void bulletupdateCooldown(double bdt);
	void ResetBullet();

	// Enemies
	void createEnemy(float x, float y, float z);
	int getEnemyPoolSize() { return this->e_poolSize; };
	static const int e_poolSize = 5;
	GameObject enemies[e_poolSize];
	Bullet fbull;

private:
	//coldown for bullets
	bool bReady;
	const float bcooldown = 0.2f;
	double bcurrentTime;
	//coldown for bullets

	// Bullets
	int lifeTime;
	Bullet* firstAvailable;
	Bullet** ptrBull;

	// Enemies
	GameObject* first;
	GameObject fenemy;
	GameObject** ptrEnemy;

};
#endif
