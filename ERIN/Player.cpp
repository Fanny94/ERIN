#include "Player.h"

Player::Player()
{
	plannedHeading = heading;
}

Player::~Player()
{
}


void Player::update(double dt)
{
	x += dt * getVx();
	y += dt * getVy();
	if (heading != plannedHeading)
	{
		computeTurn(dt);
	}

}
void Player::computeTurn(double dt)
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

void Player::turnTo(double newHeading)
{
	plannedHeading = newHeading;
}
double Player::getVx()
{
	return speed * acos(heading * M_PI / 180);
}
double Player::getVy()
{
	return speed * asin(heading * M_PI / 180);
}