#ifndef STRUCTS_H
#define STRUCTS_H

struct Position
{
	float x, y, z;
	float xPos[1];
	float yPos[1];
};

struct TSphere
{
	Vector3		m_vecCenter;
	float       m_fRadius;
};

struct TAABB
{
	Vector3 m_vecMax;
	Vector3 m_vecMin;
};

struct Wall
{
	Vector3 point;
	Vector3 normal;
};

#endif // !STRUCTS_H