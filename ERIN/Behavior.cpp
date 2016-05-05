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
	float CohesionX = 0, CohesionY = 0;
	float CohesionCount = 0;
	float cohesion = 0.09f;

	
	float enemyDist = sqrt(pow((ally.y - myself.x), 2) + pow((ally.y - myself.x), 2));
	if ((enemyDist < 2))
	{
		CohesionX += myself.x + heading;
		CohesionY += myself.y + heading;
		CohesionCount++;
	}

	if (CohesionCount > 0)
	{
		CohesionX = (CohesionX / CohesionCount) - myself.x;
		CohesionY = (CohesionY / CohesionCount) - myself.y;
		CohesionX = (CohesionX / (sqrt(pow(CohesionX, 2) + pow(CohesionY, 2)))) * VelX;
		CohesionY = (CohesionY / (sqrt(pow(CohesionX, 2) + pow(CohesionY, 2)))) * VelY;
		heading += (CohesionX - heading) * cohesion;
		heading += (CohesionY - heading) * cohesion;
	}
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

void Behavior::ObstacleAvoidance(Position myself)
{
	/*ahead = myself + velocity; //*MAX_SE_AHEAD; add this if we need to limit how far the enemy sees obstacles
	ahead2 = position + velocity; //*MAX_SE_AHEAD * 0.5; this is just ahead cut in half*/

	//Need a function that checks if the ahead instersects something that it can collide with

	//avoidanceForce = ahead - obstacleCenter; //Calculates the force that needs to be applied to the ships direction to avoid the obstacle
	//avoidanceForce = normalize(avoidanceForce) * MAXAVOIDANCEFORCE; //Here we are able to easily change the maximum force that can be applied to the ships direction

		/*var mostThreatening : Obstacle = findMostThreateningObstacle();
		var avoidance : Vector3D = new Vector3D(0, 0, 0);

		if (mostThreatening != null) {
			avoidance.x = ahead.x - mostThreatening.center.x;
			avoidance.y = ahead.y - mostThreatening.center.y;

			avoidance.normalize();
			avoidance.scaleBy(MAX_AVOID_FORCE);
		}
		else {
			avoidance.scaleBy(0); // nullify the avoidance force
		}

		return avoidance;
	}*/
}