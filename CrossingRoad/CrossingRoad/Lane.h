#pragma once
#include "RoadTile.h"
class Lane : public Object
{
protected:
	vector<Tile*> tiles;

public:
	Lane(int row) :Object(x = 0, y = row, width = 112, height = 16) {};

	virtual void Draw(CrossingRoadGame& game) {
		for (int i = 0; i < tiles.size(); i++) {
			tiles[i]->Draw(game);
		}
	}

	virtual void Update(CrossingRoadGame& game, float fElapsedTime) {
		for (int i = 0; i < tiles.size(); i++) {
			tiles[i]->Update(game, fElapsedTime);
		}
	}
};

