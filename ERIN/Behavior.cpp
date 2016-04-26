#include "Behavior.h"



Behavior::Behavior(BehaviorState state)
{
	this->behavior = Patrol;
}


Behavior::~Behavior()
{
}

void Behavior::update(Position player, Position thisEnemy)
{
	float distanceX = abs(player.x - thisEnemy.x);
	float distanceY = abs(player.y - thisEnemy.y);

	if (distanceX < this->aggroRadius && distanceY < this->aggroRadius)
	{
		this->targetInRange = true;
		this->behavior = Follow;
		Vector2 vec{ player.x - thisEnemy.x, player.y - thisEnemy.y };
		this->heading = XMConvertToDegrees(atan2f(vec.x, vec.y));
	}
	else
	{
		this->targetInRange = false;
		this->behavior = Patrol;
	}

	// logic
	//if (targetInRange == true)
	//{
	//	

	//	// fire
	//	// follow
	//}
	//else if (bulletComingTowardsMe == true)
	//{
	//	// avoid bullets ( extra )
	//}
	//else
	//{
	//	// patrol
	//}
}
