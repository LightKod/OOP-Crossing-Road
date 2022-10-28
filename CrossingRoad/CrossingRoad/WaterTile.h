#pragma once
#include "Tile.h"

class WaterTile : public Tile
{
public:
	//Thua ke ham constructor
	WaterTile() : Tile() {}
	WaterTile(int x, int y, int width, int height) :Tile(x, y, width, height) {}

	//Viet lai ham draw de ve
	void Draw1(CrossingRoadGame& game);
	void Draw2(CrossingRoadGame& game);


	virtual void Draw(CrossingRoadGame& game);
	virtual void Update(CrossingRoadGame& game, float fElapsedTime);

};

