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

	void SetX(float x) { this->x = x; };
	void SetY(float y) { this->y = y; };
	void SetZ(float z) { this->z = z; };

	string GetName() { return this->name; };
	float GetX() { return this->x; };
	float GetY() { return this->y; };
	float GetZ() { return this->z; };

	Input* input;
	TriangleVertex* triangle;
	Matrix* objectMatrix;
	//AABBBox* axisAllignedBox;

	// rotation
	void computeTurn(double deltaTime);
	void turnTo(double newHeading);

	double getVx();
	double getVy();

private:

	string name;
	float x, y, z;

	float maximumSpeed;
	float currentSpeed;
	float speed;

	bool accelerating;
	float acceleration;
	float velocity;

	float thumbLeftX;
	float thumbLeftY;

	float velocityX;
	float velocityY;

	// rotation
	double r_x = 0;
	double r_y = 0;
	double r_speed = 15; // m/s;
	double heading = 120;
	double plannedHeading = 0;
	double turnRate = 10; // deg /s
};
#endif // !PLAYER_H