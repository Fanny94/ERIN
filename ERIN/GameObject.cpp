#include "GameObject.h"

GameObject::GameObject()
	: name("noName"),
	x(0.0f), y(0.0f), z(0.0f)
{
}

GameObject::GameObject(int objectID, string name, float x, float y, float z, bool doHaveBehavior)
{
	this->objectID = objectID;
	this->name = name;
	this->x = x;
	this->y = y;
	this->z = z;
	float LO = 0.07f, HI = 0.10f, lO = 0.0006f, hI = 0.0009f;

	float Random = LO + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (HI - LO)));

	this->maximumSpeed = Random;
	this->currentSpeed = 0.0f;

	this->speed = 0.0f;

	float Ran = lO + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (hI - lO)));
	this->acceleration = Ran;

	// test triangle in gameobject
	this->triangle = new TriangleVertex[3];

	this->triangle[0] = { 0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, };
	this->triangle[1] = { 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, };
	this->triangle[2] = { -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f };

	this->objectMatrix = new Matrix();

	// behavoir
	if (doHaveBehavior == true)
	{
		this->behavior = new Behavior(Patrol);
	}
	this->pos = new Position{ this->x, this->y, this->z };

	GetEnemyPos();

	this->sphere = new TSphere();
	this->sphere->m_vecCenter = Vector3(this->x, this->y, this->z);
	this->sphere->m_fRadius = 0.1f;
}

GameObject::~GameObject()
{
	delete this->triangle;
	delete this->objectMatrix;

	delete this->pos;

	if (this->behavior)
	{
		delete this->behavior;
	}
}

void GameObject::Reset()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;

	this->speed = 0;
	this->heading = 0;

	//this->objectMatrix = new Matrix();	// Causes menory leaks
}

void GameObject::updateBehavior(Position player, GameObject* myself, GameObject** allEnemies)
{
	if (this->behavior)
	{
		Position thisEnemy = { this->x, this->y, this->z };
		this->behavior->update(player, thisEnemy);

		// static number of enemies
		//for (int i = 0; i < 4; i++)
		//{
		//	if (myself->getObjectID() != allEnemies[i]->getObjectID())
		//	{
		//		// test lines to see values quick
		//		int me = myself->getObjectID();
		//		int other = allEnemies[i]->getObjectID();

				// cohesion calculations
				this->behavior->cohesion(*myself->pos, *allEnemies[i]->pos);

				//Separation calculations
				this->behavior->separation(*myself->pos, *allEnemies[i]->pos);
			}
		}
		//		// cohesion calculations
		//		this->behavior->cohesion(*myself->pos, *allEnemies[i]->pos);
		//	}
		//}
		//this->behavior->alignment();
		//

		float radians = XMConvertToRadians((float)heading);
		this->directionX = (float)sin(radians);
		this->directionY = (float)cos(radians);
	}
}

void GameObject::update(double dt)
{
	this->pos->x = this->x;
	this->pos->y = this->y;
	this->pos->z = this->z;

	if (this->behavior->getBehavior() == Follow)
	{
		this->accelerating = true;
	}
	else
	{
		this->accelerating = false;
	}
	
	if (!accelerating)
	{
		// deacceleration
		velocityX *= 0.8f;
		velocityY *= 0.8f;
	}
	else
	{
		// Speed += ((MoveDirection * MaximumSpeed) - Speed) * AccelerationFactor
		velocityX += ((directionX * maximumSpeed) - velocityX) * abs(1.0f);
		velocityY += ((directionY * maximumSpeed) - velocityY) * abs(1.0f);

		plannedHeading = this->behavior->getHeading(); // XMConvertToDegrees(atan2f(thumbLeftX, thumbLeftY));
	}

	x = x + velocityX;
	y = y + velocityY;

	// rotation
	r_x += dt * getVx();
	r_y += dt * getVy();
	if (heading != plannedHeading)
	{
		computeTurn(dt);
	}

	this->sphere->m_vecCenter = Vector3(this->x, this->y, this->z);

	*this->objectMatrix = 
		XMMatrixRotationZ(XMConvertToRadians((float)-heading)) 
		* XMMatrixTranslation(x, y, z) 
		* XMMatrixScaling(1.0f, 1.0f, 1.0f);
}
void GameObject::computeTurn(double dt)
{
	double dh = plannedHeading - heading;
	if (dh < -180)
		dh += 360;
	if (dh > 180)
		dh -= 360;
	if (abs(dh) < turnRate * dt)
		heading = plannedHeading;
	else
	{
		int dir = 1;
		if (dh < 0)
			dir = -1;
		heading += turnRate * dt * dir;
	}

}

void GameObject::turnTo(double newHeading)
{
	plannedHeading = newHeading;
}
double GameObject::getVx()
{
	return r_speed * acos(heading * M_PI / 180);
}
double GameObject::getVy()
{
	return r_speed * asin(heading * M_PI / 180);
}

void GameObject::GetEnemyPos()
{
	/*float* EnemyPosX;
	float* EnemyPosY;*/
	int count = 0;

	float EnemyPos[1], EnemyPosY[1];
	
	EnemyPos[count] = x;
	EnemyPosY[count] = y;
	//EnemyPos[count] = y;
	//EnemyPosY[count] = y;



	pos->xPos[count] = EnemyPos[count];
	pos->yPos[count] = EnemyPosY[count];
	count++;
}