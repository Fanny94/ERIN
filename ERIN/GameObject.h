#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "Linker.h"
#include "Input.h"
#include "Structs.h"
#include "Behavior.h"

#include <string>
# define M_PI 3.14159265358979323846
using namespace std;

class GameObject
{
public:
	GameObject();
	GameObject(int objectID, string name, float x, float y, float z, bool doHaveBehavior);
	~GameObject();

	bool inUse;
	void Reset();

	void updateBehavior(Position player, GameObject* myself, GameObject** allEnemies);
	void update(double deltaTimeMs);

	void setMaxSpeed(float maxspeed) { this->maximumSpeed = maxspeed; };
	int getObjectID() { return this->objectID; };
	string getName() { return this->name; };

	TriangleVertex* triangle;
	//AABBBox* axisAllignedBox;
	Matrix* objectMatrix;
	Behavior* behavior;
	Position* pos;

	// rotation
	void computeTurn(double deltaTime);
	void turnTo(double newHeading);

	double getVx();
	double getVy();

	// flock AI
	void GetEnemyPos();

	// collision
	TSphere* sphere;

private:
	int objectID;
	string name;
	float x, y, z;

	float maximumSpeed;
	float currentSpeed;
	float speed;

	bool accelerating;
	float acceleration;

	float directionX;
	float directionY;

	float velocityX;
	float velocityY;

	// rotation
	double r_x = 0;
	double r_y = 0;
	double r_speed = 15; // m/s;
	double heading = 0;
	double plannedHeading = 0;
	double turnRate = 0.1; // deg /s
};

#endif // !GAMEOBJECT_H