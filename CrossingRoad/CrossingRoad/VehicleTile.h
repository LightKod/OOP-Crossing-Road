#pragma once
#include"Tile.h"

class VehicleTile : public Tile
{
public:
	VehicleTile() : Tile() {}
	VehicleTile(int x, int y, int width, int height) :Tile(x, y, width, height) {}
	
	void Draw(CrossingRoadGame& game);
};

