#pragma once
#include "Lane.h"
#include "RoadTile.h"
#include "Vehicle.h"
#include <cstdlib>
#include <ctime>

#include <vector>

using namespace std;

class Road : public Lane
{
public:
	Road(CrossingRoadGame* game, int row) :Lane(game, row) {
		static unsigned int seed = time(NULL);
		srand(seed++);
		int randomValue = rand() % 20;
		int randomValue1 = rand() % 30 + 40;
		int randomValue2 = rand() % 22 + 90;
		float speed;
		//DUMMY
		int random = rand() % 3;
		if (random == 1)
		{
			speed = 0.07f;
		}
		else if(random==2)
		{
			speed = -0.09f;
		}
		else
		{
			speed = 0.05f;
		}

		for (int i = 0; i < 14; i++)
		{
			tiles.push_back(new RoadTile(game, 8 * i, row));
		}
		COLOUR primary;
		COLOUR secondary;
		GetRandomColor(primary, secondary, seed++);
		vehicles.push_back(new Vehicle(game, randomValue, row, speed, primary, secondary));
		GetRandomColor(primary, secondary, seed++);
		vehicles.push_back(new Vehicle(game,randomValue1, row, speed, primary, secondary));
		GetRandomColor(primary, secondary, seed++);
		vehicles.push_back(new Vehicle(game,randomValue2, row, speed, primary, secondary));
		id = L'R';
	}

	void GetRandomColor(COLOUR& primary, COLOUR& secondary, unsigned int seed) {
		srand(seed);
		int randomValue = rand() % 6;

		switch (randomValue)
		{
		case 0:
			primary = BG_BLUE;
			secondary = BG_DARK_BLUE;
			break;
		case 1:
			primary = BG_RED;
			secondary = BG_DARK_RED;
			break;
		case 2:
			primary = BG_RED;
			secondary = BG_DARK_RED;
			break;
		case 3:
			primary = BG_YELLOW;
			secondary = BG_DARK_YELLOW;
			break;
		case 4:
			primary = BG_MAGENTA;
			secondary = BG_DARK_MAGENTA;
			break;
		case 5:
			primary = BG_GREEN;
			secondary = BG_DARK_GREEN;
			break;
		default:
			primary = BG_GREEN;
			secondary = BG_DARK_GREEN;
			break;
		}
	}
	void Draw() {
		Lane::Draw();
		for (int i = 0; i < vehicles.size(); i++) {
			vehicles[i]->Draw();
		}
	}
	void Update(float fElapsedTime) {
		Lane::Update(fElapsedTime);
		for (int i = 0; i < vehicles.size(); i++) {
			vehicles[i]->Update(fElapsedTime);
		}
	}

	virtual void SetCollisionMatrix() {
		for (int i = 0; i < vehicles.size(); i++) {
			vehicles[i]->SetCollisionMatrix();
		}
	}
};

