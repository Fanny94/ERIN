#ifndef STRUCTS_H
#define STRUCTS_H

struct Position
{
	float x, y, z;
	float xPos[1];
	float yPos[1];
};

struct TriangleVertex
{
	float x, y, z;
	float r, g, b;
};

struct TSphere
{
	Vector3		m_vecCenter;
	float       m_fRadius;
};

#endif // !STRUCTS_H
