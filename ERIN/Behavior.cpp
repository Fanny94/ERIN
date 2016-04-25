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

	if (abs(player.x) < this->aggroRadius && abs(player.y) < this->aggroRadius)
	{
		this->targetInRange = true;
		this->behavior = Follow;
		this->heading = XMConvertToDegrees(atan2f(player.x, player.y));
	}
	else
	{
		this->targetInRange = false;
		this->behavior = Patrol;
	}

	/*this->behavior = Follow;
	this->heading = XMConvertToDegrees(atan2f(player.x, player.y));*/

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
