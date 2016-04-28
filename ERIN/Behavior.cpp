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

	/////////////////TA INTE BORT
	//Måste lösa looparna n shit
	//float EnemyDistanceX = abs(thisEnemy.x - Po.xPos[i]);
	//float EnemyDistanceY = abs(thisEnemy.y - Po.yPos[i]);

	/*float EnemyDistanceX1 = abs(thisEnemy.x - Po.xPos[1]);
	float EnemyDistanceY1 = abs(thisEnemy.y - Po.yPos[1]);
	float EnemyDistanceX2 = abs(thisEnemy.x - Po.xPos[2]);
	float EnemyDistanceY2 = abs(thisEnemy.y - Po.yPos[2]);
	float EnemyDistanceX3 = abs(thisEnemy.x - Po.xPos[3]);
	float EnemyDistanceY3 = abs(thisEnemy.y - Po.yPos[3]);
	float EnemyDistanceX4 = abs(thisEnemy.x - Po.xPos[4]);
	float EnemyDistanceY4 = abs(thisEnemy.y - Po.yPos[4]);
	float EnemyDistanceX5 = abs(thisEnemy.x - Po.xPos[5]);
	float EnemyDistanceY5 = abs(thisEnemy.y - Po.yPos[5]);


	if (EnemyDistanceX1 < 3.0f || EnemyDistanceY1 < 3.0f || EnemyDistanceX2 < 3.0f || EnemyDistanceY2 < 3.0f || EnemyDistanceX3 < 3.0f || EnemyDistanceY3 < 3.0f || EnemyDistanceX4 < 3.0f || EnemyDistanceY4 < 3.0f || EnemyDistanceX5 < 3.0f || EnemyDistanceY5 < 3.0f)*/

	/*if(EnemyDistanceX < 3.0f || EnemyDistanceY < 3.0f)
	{
	for (int i = 0; i < 4; i++)
	{
			OffS = OffS - EnemyDistanceX;
			OffSY = OffSY - EnemyDistanceY;
			Vector2 vec{ OffS, OffSY };
			this->heading = XMConvertToDegrees(atan2f(vec.x, vec.y));

		}
	}*/
	/////////////////TA INTE BORT


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


Vector2 Behavior::cohesion(Position ally, Position myself)
{
	Vector2 forceVec = Vector2(0, 0);
	//vector<int> CenterOfMass;

	//int Neighbors;
	//double Average;

	//// Loop through all enemies and check so that it is not checking itself as a someone else
	//for (myself)
	//{
	//	if (!myself)
	//	{
	//		force += Vector2(1, 2);
	//		CenterOfMass += thisEnemy;
	//		Neighbors++
	//	}
	//}

	//// If there are Neighbors nearby
	//if (Neighbors > 0)
	//{
	//	// Calculate the average of CenterOfMass with Neighbors as parameter
	//	Average;
	//	ForceVec = CenterOfMass - otherEnemy;
	//	ForceVec = ForceVec.Normalize;
	//}
	return forceVec;
}

void Behavior::alignment()
{
}

void Behavior::separation(Position thisEnemy, Position otherEnemy)
{
	float DistanceX = abs(thisEnemy.x - otherEnemy.x);
	float DistanceY = abs(thisEnemy.y - otherEnemy.y);
	float SeperationDist = 25.0f;
	int Counter = 0;
	float AvoidDistance = 0.0f;

	//float GitDist = (((thisEnemy.x - otherEnemy.x)*(thisEnemy.x - otherEnemy.x)) + 
	//					((thisEnemy.y - otherEnemy.y)*(thisEnemy.y - otherEnemy.y)));

	//Vector2 Dist = { EnemyDistanceX, EnemyDistanceY };
	// = { 0, 0, 0 };

	if (DistanceX < 5.0f && DistanceY < 5.0f)
	{
		OffS = OffS - DistanceX;
		OffSY = OffSY - DistanceY;
		Vector2 vec{ OffS, OffSY };
		this->heading = XMConvertToDegrees(atan2f(vec.x, vec.y));
	}


	//return OffS;
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