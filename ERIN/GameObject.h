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

	void Createsphere();

	void updateBehavior(Position player, GameObject* myself, GameObject* allEnemies);
	void update(double deltaTimeMs);
	void reset();

	void setObjectID(int objectID) { this->objectID = objectID; };
	void setObjectName(string name) { this->name = name; };
	void setObjectPosX(float x) { this->x = x; };
	void setObjectPosY(float y) { this->y = y; };
	void setObjectPosZ(float z) { this->z = z; };

	void setMaxSpeed(float maxspeed) { this->maximumSpeed = maxspeed; };
	void setAcceleration(float acceleration) { this->acceleration = acceleration; };

	int enemyCount = 5;

	int getObjectID() { return this->objectID; };
	string getName() { return this->name; };

	TriangleVertex* triangle;
	Matrix* objectMatrix;
	Behavior* behavior;
	Position* pos;

	// rotation
	void computeTurn(double deltaTime);
	void turnTo(double newHeading);

	double getVx();
	double getVy();

	// flock AI

	// collision
	TSphere* sphere;

	// objectpool handling
	void setInUse(bool inUse) { this->inUse = inUse; };
	bool getInUse() { return this->inUse; };
	GameObject* next;
	void setNext(GameObject* Next) { this->next = Next; };

private:
	int objectID;
	string name;
	float x, y, z;

	float maximumSpeed;
	float speed = 0.0f;

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