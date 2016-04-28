#ifndef BULLET_H
#define BULLET_H

#include "Linker.h"

class Bullet
{
public:
	Bullet();
	~Bullet();

	void update();
	void iniBullet(float x, float y, int lifeTime);
	bool getInUse() { return this->inUse; };


private:
	int timeLeft; //How long a bullet will last
	float x, y;
	bool inUse;
	float damage; // if needed

};
#endif // !BULLET_H
