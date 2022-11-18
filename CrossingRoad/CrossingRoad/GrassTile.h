#pragma once
#include "Tile.h"

class GrassTile : public Tile
{
public:
	//Thua ke ham constructor
	GrassTile(CrossingRoadGame* game) : Tile(game) {}
	GrassTile(CrossingRoadGame* game, int x, int y) :Tile(game, x, y, width = 8, height = 8) {}

	//Viet lai ham draw de ve

	virtual void Draw();
	virtual void Update(float fElapsedTime);

};

