#include "Behavior.h"



Behavior::Behavior(BehaviorState state)
{
	this->behavior = Patrol;
}


Behavior::~Behavior()
{
}

void Behavior::update(Position player, Position myself)
{
	float distanceX = abs(player.x - myself.x);
	float distanceY = abs(player.y - myself.y);




	if (distanceX < this->aggroRadius && distanceY < this->aggroRadius)
	{
		this->targetInRange = true;
		this->behavior = Follow;
		Vector2 vec{ player.x - myself.x, player.y - myself.y };
		this->heading = XMConvertToDegrees(atan2f(vec.x, vec.y));
	}
	else
	{
		this->targetInRange = false;
		this->behavior = Patrol;
	}


	/*float EnemyDistanceX = abs(thisEnemy.x - otherEnemy.x);
	float EnemyDistanceY = abs(thisEnemy.y - otherEnemy.y);

	Vector2 Dist = { EnemyDistanceX, EnemyDistanceY };

	Vector3 OffS = { 0, 0, 0 };

	if (EnemyDistanceX < 50)
	{
		OffS = OffS - Dist;

	}*/
}


void Behavior::cohesion(Position myself, Position ally)
{
	/*float calc1 = myself.x + ally.x;
	float calc2 = myself.y + ally.y;
	int N = 5;
	
	float EnemyDistanceX = abs(myself.x - ally.x);
	float EnemyDistanceY = abs(myself.y - ally.y);
	if (EnemyDistanceX > 5.0f && EnemyDistanceY > 5.0f)
	{
		Vector2 forceVec = Vector2(calc1 / (N - 1), calc2 / (N - 1));
		Vector2 compVec = { ally.x, ally.y };

		Vector2 finalVec = (forceVec - compVec) / 100;
		this->heading = XMConvertToDegrees(atan2f(finalVec.x, finalVec.y));
	}
	vector<int> CenterOfMass;

	int Neighbors;
	double Average;

	 //Loop through all enemies and check so that it is not checking itself as a someone else
	for (myself)
	{
		if (!myself)
		{
			force += Vector2(1, 2);
			CenterOfMass += thisEnemy;
			Neighbors++
		}
	}

	//If there are Neighbors nearby
	if (Neighbors > 0)
	{
		// Calculate the average of CenterOfMass with Neighbors as parameter
		Average;
		ForceVec = CenterOfMass - otherEnemy;
		ForceVec = ForceVec.Normalize;
	}*/
}

void Behavior::alignment()
{
}

void Behavior::separation(Position myself, Position ally)
{

	//Calculates the distance between 2 enemies
	float EnemyDistanceX = abs(myself.x - ally.x);
	float EnemyDistanceY = abs(myself.y - ally.y);

	//If an enemy is too close to another enemy it will enter and try and correct it
	if(EnemyDistanceX < 0.7f && EnemyDistanceY < 0.7f)
	{
	//Offset for the enemies direction in X
	OffS = OffS - EnemyDistanceX;
	//Offset for the enemies direction in Y
	OffSY = OffSY - EnemyDistanceY;
	//Puts these offsets in a vector
	Vector2 vec{ OffS, OffSY };
	//Converts the values to degrees so that it can affect the heading of the enemy
	this->heading = XMConvertToDegrees(atan2f(vec.x, vec.y));
	}
	
	
	/*float AvoidWeight = 0.1f;
	float NewAcc[3];

	for (int i = thisEnemy.x; i <= thisEnemy.z; i++)
	{
	NewAcc[i] = (AvoidWeight * )
	}
	/*if (DistanceX > 0 && DistanceX < SeperationDist)
	{
	vector<float> Diff(DistanceX, DistanceY);
	Counter++;
	}*/
}