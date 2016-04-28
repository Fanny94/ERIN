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

	void update(Position player, Position myself);

	// flock AI
	Vector2 cohesion(Position ally, Position myself);
	void alignment();
	void separation(Position thisEnemy, Position otherEnemy);

	float OffS;
	float OffSY;

	// AI
	double getHeading() { return this->heading; };
	BehaviorState getBehavior() { return this->behavior; };

private:
	BehaviorState behavior;
	bool targetInRange;
	bool bulletComingTowardsMe;

	double heading;
	float aggroRadius = 10.0f;

	// flock AI
	Position Po;
	Position* pPo;
};

#endif // !BEHAVIOR_H