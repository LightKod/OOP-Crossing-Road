#pragma once
#include"Tile.h"

class RoadTile : public Tile
{
public:
	RoadTile() : Tile() {}
	RoadTile(int x, int y) :Tile(x, y, width = 16, height = 16) {}

	void Draw(CrossingRoadGame& game);
};

