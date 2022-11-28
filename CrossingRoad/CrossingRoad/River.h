#pragma once
#include "Lane.h"
#include "WaterTile.h"
#include "Duck.h"
#include <string>
#include <sstream>
class River : public Lane
{
public:
	River(CrossingRoadGame* game, int row) :Lane(game, row) {
		for (int i = 0; i < 14; i++)
		{
			tiles.push_back(new WaterTile(game, 8 * i, row));
		}
		id = L'W';
		int randomValue = (rand() % 4) * 8;
		int randomValue1 = (rand() % 4) * 8 + 32;
		int randomValue2 = (rand() % 4) * 8 + 64;
		vehicles.push_back(new Duck(game, randomValue, row, 1));
		vehicles.push_back(new Duck(game, randomValue1, row, 1));
		vehicles.push_back(new Duck(game, randomValue2, row, 1));


	}

	River(CrossingRoadGame* game, wstring dataString) : Lane(game, dataString) {
		for (int i = 0; i < 14; i++)
		{
			tiles.push_back(new WaterTile(game, 8 * i, y));
		}
		id = L'W';
	}

	void Update(float fElapsedTime) {
		Lane::Update(fElapsedTime);
		for (int i = 0; i < vehicles.size(); i++) {
			vehicles[i]->Update(fElapsedTime);
		}
	}

	void SetCollisionMatrix() {
		game->FillCollisionMatrix(0, y, 112, y + 7, true);
		for (int i = 0; i < vehicles.size(); i++) {
			vehicles[i]->SetCollisionMatrix();
		}
	}
};

