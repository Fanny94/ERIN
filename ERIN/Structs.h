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
};
#endif // !STRUCTS_H
