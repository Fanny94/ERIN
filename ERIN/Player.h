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

	//player health
	int HP = 6;
	void hpCooldown(double hpdt);
	bool getHpCooldown() { return this->hpReady; };
	void setHpCooldown(bool hpReady) { this->hpReady = hpReady; };

	void playerInput();
	void update(double deltaTime);

	void PlayerReset();

	void NewFloorReset();

	void SetX(float x) { this->x = x; };
	void SetY(float y) { this->y = y; };
	void SetZ(float z) { this->z = z; };

	string GetName() { return this->name; };
	float getX() { return this->x; };
	float getY() { return this->y; };
	float getZ() { return this->z; };

	Input* input;

	// turret magic
	Matrix* objectMatrix; // is replaced by shipMatrix
	Matrix* shipMatrix;
	Matrix* turretMatrix;

	Position* shipPos;
	Position* turretPos;

	// rotation
	void computeTurn(double deltaTime);
	void turretComputeTurn(double deltaTime);
	void turnTo(double newHeading);

	double getHeading() { return turrent_heading; };

	double getVx();
	double getVy();
	double getTVx();
	double getTVy();

	// collision
	TSphere* sphere;

	//test
	float thumbRightX;
	float thumbRightY;

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

	//cooldown for damage
	bool hpReady;
	const float hpcooldown = 4.0f;
	double hpcurrentTime;
	//cooldown for damage
};
#endif // !PLAYER_H