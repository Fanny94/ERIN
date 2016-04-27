#ifndef STRUCTS_H
#define STRUCTS_H

struct TriangleVertex
{
	float x, y, z;
	float r, g, b;
};

struct AABBBox
{
	XMFLOAT3 points[8];
	XMFLOAT3 min;
	XMFLOAT3 max;
};

struct AABBVertex
{
	XMFLOAT3 points[24];
};
#endif // !STRUCTS_H
