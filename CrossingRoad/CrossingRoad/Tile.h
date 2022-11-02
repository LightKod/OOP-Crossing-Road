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
	Tile() : Object() { width = 8; height = 8; x = 0; y = 0; }
	Tile(int x, int y, int width, int height) :Object(x, y, width, height) {}

};

