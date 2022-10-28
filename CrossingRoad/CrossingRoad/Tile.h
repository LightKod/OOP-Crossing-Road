#pragma once

#include "Object.h"

class Object;

class Tile : public Object
{
protected:
	float time = 0;
	bool spriteIndex = false;
public:
	//Thua ke ham constructor
	Tile() : Object() {}
	Tile(int x, int y, int width, int height) :Object(x, y, width, height){}

};

