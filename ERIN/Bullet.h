#ifndef BULLET_H
#define BULLET_H

class Bullet
{
public:
	Bullet();
	~Bullet();

	void update();

	bool getInUse() { return this->inUse; };

private:
	float x, y;
	bool inUse;
	float damage; // if needed
};
#endif // !BULLET_H
