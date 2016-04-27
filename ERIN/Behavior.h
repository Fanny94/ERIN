#ifndef BEHAVIOR_H
#define BEHAVIOR_H
#include "Linker.h"
#include "Structs.h"

typedef enum
{
	Patrol = 0,
	Follow = 1,
	Fire = 2,
}BehaviorState;

class Behavior
{
public:
	Behavior(BehaviorState state);
	~Behavior();

	//Position* pos;

	/*
	Patrol
	Follow player
	Fire
	*/

	void update(Position player, Position thisEnemy);
	void seperation(Position thisEnemy, Position otherEnemy);
	//Vector2 Cohesion(Position thisEnemey, Position otherEnemy);
	double getHeading() { return this->heading; };
	BehaviorState getBehavior() { return this->behavior; };

	float OffS;
	float OffSY;

private:
	Position Po;
	Position* pPo;
	BehaviorState behavior;
	bool targetInRange;
	bool bulletComingTowardsMe;

	double heading;
	float aggroRadius = 10.0f;
	float fireRadius = 500.0f;
};

#endif // !BEHAVIOR_H