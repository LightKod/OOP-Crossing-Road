#pragma once
#include "Lane.h"
#include "RoadTile.h"
class Road : public Lane
{
public:
	Road(int row) :Lane(row) {
		for (int i = 0; i < 7; i++)
		{
			tiles.push_back(new RoadTile(16 * i, row));
		}
	}
};

