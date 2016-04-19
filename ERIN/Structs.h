#ifndef STRUCTS_H
#define STRUCTS_H

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
