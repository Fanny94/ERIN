#ifndef PLAYER_H
#define PLAYER_H

# define M_PI           3.14159265358979323846
#include "Linker.h"

class Player
{
public:
	Player();
	~Player();

	void update(double deltaTime);
	void computeTurn(double deltaTime);
	void turnTo(double newHeading);

	double getVx();
	double getVy();

private:
	double x = 0;
	double y = 0;
	double speed = 15; // m/s;
	double heading = 120;
	double plannedHeading = 0;
	double turnRate = 3; // deg /s
};
#endif // !PLAYER_H