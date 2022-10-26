#pragma once

#include "Object.h"

class Object;

class Tile : public Object
{
public:
	//Thua ke ham constructor
	Tile() : Object() {}
	Tile(int x, int y, int width, int height) :Object(x, y, width, height){}

	//Viet lai ham draw de ve
	virtual void Draw(CrossingRoadGame& game);
	virtual void Update(CrossingRoadGame& game, float fElapsedTime);
};

