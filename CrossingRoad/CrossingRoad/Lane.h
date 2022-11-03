#pragma once
#include "Tile.h"
#include <vector>

using namespace std;

class Lane : public CrossingRoadGame::Object
{
protected:
	vector<Tile*> tiles;

public:
	Lane(CrossingRoadGame*game, int row) :Object(game, x = 0, y = row, width = 112, height = 16) {};

	virtual void Draw() {
		for (int i = 0; i < tiles.size(); i++) {
			tiles[i]->Draw();
		}
	}

	virtual void Update(float fElapsedTime) {
		for (int i = 0; i < tiles.size(); i++) {
			tiles[i]->Update(fElapsedTime);
		}
	}
};

