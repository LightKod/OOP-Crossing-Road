#pragma once
#include "Tile.h"

class WaterTile : public Tile
{
public:
	//Thua ke ham constructor
	WaterTile() : Tile() {}
	WaterTile(int x, int y) :Tile(x, y, width = 8, height = 8) {}

	//Viet lai ham draw de ve
	void Draw1(CrossingRoadGame& game);
	void Draw2(CrossingRoadGame& game);


	virtual void Draw(CrossingRoadGame& game);
	virtual void Update(CrossingRoadGame& game, float fElapsedTime);

};

