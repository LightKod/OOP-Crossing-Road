#pragma once

#include "Object.h"

class Object;

class Tile : public Object
{
	float time;
public:
	//Thua ke ham constructor
	Tile() : Object() {}
	Tile(int x, int y, int width, int height) :Object(x, y, width, height){}

	//Viet lai ham draw de ve
	virtual void DrawWater1(CrossingRoadGame& game);
	virtual void DrawWater2(CrossingRoadGame& game);
	virtual void Draw1(CrossingRoadGame& game, float time);
	virtual void Draw2(CrossingRoadGame& game, float time);
	virtual void Update1(CrossingRoadGame& game, float fElapsedTime);
	virtual void Update2(CrossingRoadGame& game, float fElapsedTime);
};

