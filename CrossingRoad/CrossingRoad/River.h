#pragma once
#include "Lane.h"
#include "WaterTile.h"
class River : public Lane
{
public:
	River(CrossingRoadGame* game, int row) :Lane(game, row) {
		for (int i = 0; i < 14; i++)
		{
			tiles.push_back(new WaterTile(game, 8 * i, row));
		}
		id = L'W';
	}
};

