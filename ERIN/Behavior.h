#ifndef BEHAVIOR_H
#define BEHAVIOR_H
#include "Linker.h"
#include "Structs.h"

typedef enum
{
	Patrol = 0,
	Follow = 1,
	Fire = 2,
	Avoid = 3,
}BehaviorState;

class Behavior
{
public:
	Behavior(BehaviorState state);
	~Behavior();

	void update(Position player, Position myself);

	void updateSpecial(Position player, Position myself);

	float VelX;
	float VelY;
	
	// flock AI
	void cohesion(Position myself, Position ally);
	void alignment();
	void separation(Position myself, Position ally);

	float OffS;
	float OffSY;

	// AI
	double getHeading() { return this->heading; };
	BehaviorState getBehavior() { return this->behavior; };

	void CornerAvoidance(Position myself);

private:
	BehaviorState behavior;
	bool targetInRange;
	bool bulletComingTowardsMe;

	double heading;
	float aggroRadius = 100.0f;
	float avoidRadius = 10.0f;

	// flock AI
	Position Po;
	Position* pPo;
};

#endif // !BEHAVIOR_H