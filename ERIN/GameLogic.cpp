#include "GameLogic.h"

GameLogic::GameLogic()
{
}


GameLogic::~GameLogic()
{
}

bool GameLogic::AABBtoAABB(vector<AABBBox*> box1, vector<AABBBox*> box2)
{

	if(box1[0]->max.x > box2[0]->min.x &&
		box1[0]->min.x < box2[0]->max.x &&
		box1[1]->max.y > box2[1]->min.y &&
		box1[1]->min.y < box2[1]->max.y &&
		box1[2]->max.z > box2[2]->min.z &&
		box1[2]->min.z < box2[2]->max.z)
	{
		return true;
		cout << "hit";
		
	}

	else
	{		
		return false;
	
	}

}
