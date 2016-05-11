#include "GameObject.h"

GameObject::GameObject()
	: name("noName"),
	x(0.0f), y(0.0f), z(0.0f)
{
	this->objectMatrix = new Matrix();

	this->behavior = new Behavior(Patrol);
	this->pos = new Position{ this->x, this->y, this->z };

	this->sphere = new TSphere();
	this->sphere->m_vecCenter = Vector3(this->x, this->y, this->z);
	this->sphere->m_fRadius = 0.5f;
}

GameObject::GameObject(int objectID, string name, float x, float y, float z, bool doHaveBehavior)
{
	this->objectID = objectID;
	this->name = name;
	this->x = x;
	this->y = y;
	this->z = z;

	// speed
	float LO = 0.07f, HI = 0.15f, lO = 0.0006f, hI = 0.0009f;
	float Random = LO + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (HI - LO)));
	this->maximumSpeed = Random;

	float Ran = lO + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (hI - lO)));
	this->acceleration = Ran;

	this->objectMatrix = new Matrix();

	// behavoir
	if (doHaveBehavior == true)
	{
		this->behavior = new Behavior(Patrol);
	}
	this->pos = new Position{ this->x, this->y, this->z };

	this->sphere = new TSphere();
	this->sphere->m_vecCenter = Vector3(this->x, this->y, this->z);
	this->sphere->m_fRadius = 0.5f;

	this->behavior->VelX = getVelocityX();
	this->behavior->VelY = getVelocityY();
}

GameObject::~GameObject()
{
	delete this->objectMatrix;
	delete this->pos;
	delete this->sphere;

	if (this->behavior)
	{
		delete this->behavior;
	}
}

void GameObject::updateBehavior(Position player, GameObject* myself, GameObject* allEnemies)
{
	if (this->behavior)
	{
		Position thisEnemy = { this->x, this->y, this->z };
		this->behavior->update(player, thisEnemy);

		// static number of enemies
		for (int i = 0; i < 4; i++)
		{
			if (myself->getObjectID() != allEnemies[i].getObjectID())
			{
				// test lines to see values quick
				int me = myself->getObjectID();
				int other = allEnemies[i].getObjectID();

				// cohesion calculations
				this->behavior->cohesion(*myself->pos, *allEnemies[i].pos);

				// separation calculations
				this->behavior->separation(*myself->pos, *allEnemies[i].pos);
			}
		}
		//this->behavior->alignment();

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

void GameObject::reset()
{
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;

	this->heading = 0;
	this->plannedHeading = 0;

	this->speed = 0.0f;

	delete this->objectMatrix;
	this->objectMatrix = new Matrix();

	this->pos->x = this->x;
	this->pos->y = this->y;
	this->pos->z = this->z;

	this->sphere->m_vecCenter = Vector3(this->x, this->y, this->z);
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


//Special Enemy functions

void GameObject::SpecialReset()
{
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;

	this->heading = 0;
	this->plannedHeading = 0;

	this->speed = 0.0f;

	delete this->objectMatrix;
	this->objectMatrix = new Matrix();

	this->pos->x = this->x;
	this->pos->y = this->y;
	this->pos->z = this->z;

	this->sphere->m_vecCenter = Vector3(this->x, this->y, this->z);
}


void GameObject::updateSpecialBehavior(Position player, GameObject* myself, GameObject* allEnemies)
{
	if (this->behavior)
	{
		Position thisEnemy = { this->x, this->y, this->z };
		this->behavior->updateSpecial(player, thisEnemy);

		// static number of enemies
		for (int i = 0; i < 2; i++)
		{
			if (myself->getObjectID() != allEnemies[i].getObjectID())
			{
				// test lines to see values quick
				int me = myself->getObjectID();
				int other = allEnemies[i].getObjectID();

				// separation calculations
				this->behavior->separation(*myself->pos, *allEnemies[i].pos);
				this->behavior->CornerAvoidance(*myself->pos);
			}
		}
		//this->behavior->alignment();

		float radians = XMConvertToRadians((float)heading);
		this->directionX = (float)sin(radians);
		this->directionY = (float)cos(radians);
	}
}

void GameObject::SpecialupdateCooldown(double sdt)
{
	if (this->scooldown <= this->scurrentTime)
	{
		this->scurrentTime = 0.0f;
		//this->sReady = true;
	}
	else
	{
		this->scurrentTime += sdt;
	}
}