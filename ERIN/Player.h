#ifndef PLAYER_H
#define PLAYER_H
#include "Linker.h"
#include "Input.h"
#include "Structs.h"

# define M_PI 3.14159265358979323846
using namespace std;

class Player
{
public:
	Player();
	Player(string name, float x, float y, float z);
	~Player();

	void playerInput();
	void update(double deltaTime);

	void stopX();
	void stopY();

	void setThumbLeftX(float x) { this->thumbLeftX = x; };
	void setThumbLeftY(float y) { this->thumbLeftY = y; };

	void setAccelerating(bool acc) { this->accelerating = acc; };
	void SetX(float x) { this->x = x; };
	void SetY(float y) { this->y = y; };
	void SetZ(float z) { this->z = z; };

	void setSpeed(float speed) { this->speed = speed; };
	void setVelocityX(float vX) { this->velocityX = vX; };
	void setVelocityY(float vY) { this->velocityY = vY; };

	string GetName() { return this->name; };
	float GetX() { return this->x; };
	float GetY() { return this->y; };
	float GetZ() { return this->z; };

	float getSpeed() { return this->speed;  };
	float getVelocityX() { return this->velocityX; };
	float getVelocityY() { return this->velocityY; };

	Input* input;

	// turret magic
	TriangleVertex* ship;
	TriangleVertex* turret;
	Matrix* shipMatrix;
	Matrix* turretMatrix;

	Position* shipPos;
	Position* turretPos;

	// rotation
	void computeTurn(double deltaTime);
	void turretComputeTurn(double deltaTime);
	void turnTo(double newHeading);

	double getVx();
	double getVy();
	double getTVx();
	double getTVy();

	// collision
	TSphere* sphere;

private:

	string name;
	float x, y, z;

	float maximumSpeed;
	float speed;

	bool accelerating;
	float acceleration;
	float velocity;

	float thumbLeftX;
	float thumbLeftY;
	float thumbRightX;
	float thumbRightY;

	float velocityX;
	float velocityY;

	// ship rotation
	double r_x = 0;
	double r_y = 0;
	double r_speed = 10; // m/s;
	double heading = 0;
	double plannedHeading = 0;
	double turnRate = 0.5; // deg /s

	// turrent rotation
	double tr_x = 0;
	double tr_y = 0;
	double tr_speed = 20; // m/s;
	double turrent_heading = 0;
	double turret_plannedHeading = 0;
	double turret_turnRate = 1.0; // deg /s	
};
#endif // !PLAYER_H