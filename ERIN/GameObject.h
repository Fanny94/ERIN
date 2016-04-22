#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "Linker.h"
#include "Input.h"
#include "Structs.h"

#include <string>
using namespace std;

class GameObject
{
public:
	GameObject();
	GameObject(string name, float x, float y, float z);
	~GameObject();

	void behavior();
	void update(double deltaTimeMs);

	void SetX(float x) { this->x = x; };
	void SetY(float y) { this->y = y; };
	void SetZ(float z) { this->z = z; };

	string GetName() { return this->name; };
	float GetX() { return this->x; };
	float GetY() { return this->y; };
	float GetZ() { return this->z; };

	TriangleVertex* triangle;
	AABBBox* axisAllignedBox;
	Matrix* objectMatrix;

private:

	string name;
	float x, y, z;

	float maximumSpeed;
	float currentSpeed;
	float speed;

	bool accelerating;
	float acceleration;
	float velocity;

	float velocityX;
	float velocityY;
};

#endif // !GAMEOBJECT_H