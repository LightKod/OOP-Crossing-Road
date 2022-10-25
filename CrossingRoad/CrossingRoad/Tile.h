#pragma once

#include "Object.h"

class Tile : public Object
{
public:
	void Draw(CrossingRoadGame & game, int x, int y);
};

