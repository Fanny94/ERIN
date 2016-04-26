#include "Behavior.h"



Behavior::Behavior(BehaviorState state)
{
	this->behavior = Patrol;
}


Behavior::~Behavior()
{
}

//DO NOT REMOVE
/*Vector2 Behavior::Cohesion(Position thisEnemy, Position otherEnemy)
{
	vector<int> ForceVec;
	vector<int> CenterOfMass;
	int Neighbors;
	double Average;

	//Loop through all enemies and check so that it is not checking itself as a someone else
	for (thisEnemy)
	{
		if (!thisEnemy)
		{
			CenterOfMass += thisEnemy;
			Neighbors++
		}
	}

	 //If there are Neighbors nearby
	if (Neighbors > 0)
	{
		//Calculate the average of CenterOfMass with Neighbors as parameter
		Average;
		ForceVec = CenterOfMass - otherEnemy;
		ForceVec = ForceVec.Normalize;
	}
	return ForceVec;
}*/

void Behavior::seperation(Position thisEnemy, Position otherEnemy)
{
	float DistanceX = abs(thisEnemy.x - otherEnemy.x);
	float DistanceY = abs(thisEnemy.y - otherEnemy.y);
	float SeperationDist = 25.0f;
	int Counter = 0;


	if (DistanceX > 0 && DistanceX < SeperationDist)
	{
		vector<float> Diff(DistanceX, DistanceY);
		Counter++;
	}


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
