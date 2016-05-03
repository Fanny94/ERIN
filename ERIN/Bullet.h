#ifndef BULLET_H
#define BULLET_H

#include "Linker.h"
#include "Structs.h"
#include <ctime>
#include <time.h>

class Bullet
{
public:
	Bullet();
	~Bullet();

	TriangleVertex* triangle;
	
	Bullet* getNext() const { return state.Next; };
	void update(double deltaTime);
	void iniBullet(float x, float y, float z, int lifeTime);
	bool getInUse() { return this->inUse; };
	void setNext(Bullet* Next) { state.Next = Next; };
	
	bool canFire = false;
	int countdown = 60;

	Position* bulletPos;
	Matrix* bulletMatrix;
	//bool inUse;
	int lastFire = 300;
	int timeLeft = 700; //How long a bullet will last
	bool inUse;
	
	union 
	{
		struct alive
		{
			float x, y, z;
			float Velx, Vely;
		} alive;
		
		Bullet* Next;
	} state;


private:


	double bullet_heading = 0;
	double bullet_plannedHeading = 0;

	
	
	
	float maxspd = 0.02f;
	
	float damage; // if needed

};
#endif // !BULLET_H
