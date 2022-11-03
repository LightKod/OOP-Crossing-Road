#pragma once
#include "Lane.h"
#include "RoadTile.h"
class Road : public Lane
{
public:
	Road(CrossingRoadGame* game, int row) :Lane(game, row) {
		for (int i = 0; i < 7; i++)
		{
			tiles.push_back(new RoadTile(game, 16 * i, row));
		}
	}
};

