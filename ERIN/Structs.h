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

struct AABBBox
{
	XMFLOAT3 min;
	XMFLOAT3 max;
};
#endif // !STRUCTS_H
