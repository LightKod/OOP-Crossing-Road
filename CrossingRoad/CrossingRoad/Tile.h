#pragma once

#include "CrossingRoadGame.h"

class Tile : public CrossingRoadGame::Object
{
protected:
	float time = 0;
	bool spriteIndex = false;
public:
	//Thua ke ham constructor
	Tile(CrossingRoadGame* game) : CrossingRoadGame::Object(game) { width = 8; height = 8; x = 0; y = 0; }
	Tile(CrossingRoadGame* game, int x, int y, int width, int height) :Object(game, x, y, width, height) {}

	void SetRow(int row) {
		y = row;
	}
};

