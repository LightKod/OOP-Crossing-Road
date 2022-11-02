#pragma once
#include "Lane.h"
#include "WaterTile.h"
class River : public Lane
{
public:
	River(int row) :Lane(row) {
		for (int i = 0; i < 14; i++)
		{
			tiles.push_back(new WaterTile(8 * i, row));
		}
	}
};

