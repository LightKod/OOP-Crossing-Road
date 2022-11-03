#pragma once
#include "Tile.h"

class RoadTile : public Tile
{
public:
	RoadTile(CrossingRoadGame* game) : Tile(game) {}
	RoadTile(CrossingRoadGame* game,int x, int y) :Tile(game, x, y, width = 16, height = 16) {}
	virtual void Draw();
};

