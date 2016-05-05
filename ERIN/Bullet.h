#ifndef BULLET_H
#define BULLET_H

#include "Linker.h"
#include "Structs.h"

class Bullet
{
public:
	Bullet();
	~Bullet();
	
	Bullet* getNext() const { return state.Next; };
	
	void update();
	void iniBullet(float x, float y, float z, int lifeTime);
	
	bool getInUse() { return this->inUse; };
	void setInUse(bool inUse) { this->inUse = inUse; };
	
	void setNext(Bullet* Next) { state.Next = Next; };
	
	Position* bulletPos;
	Matrix* bulletMatrix;
	int timeLeft = 700; //How long a bullet will last
	

	union 
	{
		struct alive
		{
			float x, y, z;
			float Velx, Vely;
		} alive;
		
		Bullet* Next;
	} state;

	double bullet_heading = 0;

private:
	bool inUse;
	float maxspd = 0.08f;
};
#endif // !BULLET_H
