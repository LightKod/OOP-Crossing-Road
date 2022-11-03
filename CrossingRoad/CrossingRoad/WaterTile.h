#pragma once
#include "Tile.h"

class WaterTile : public Tile
{
public:
	//Thua ke ham constructor
	WaterTile(CrossingRoadGame* game) : Tile(game) {}
	WaterTile(CrossingRoadGame* game,int x, int y) :Tile(game, x, y, width = 8, height = 8) {}

	//Viet lai ham draw de ve
	void Draw1();
	void Draw2();


	virtual void Draw();
	virtual void Update(float fElapsedTime);

};

