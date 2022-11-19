#pragma once
#include "Tile.h"

class RoadTile : public Tile
{
public:
	RoadTile(CrossingRoadGame* game) : Tile(game) {}
	RoadTile(CrossingRoadGame* game,int x, int y) :Tile(game, x, y, width = 8, height = 8) {}
	virtual void Draw();
};

