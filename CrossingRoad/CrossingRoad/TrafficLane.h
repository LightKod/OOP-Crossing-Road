#pragma once
#include "Lane.h"
#include "Road.h"
#include "RoadTile.h"
#include "Vehicle.h"
#include <cstdlib>
#include <ctime>
#include <string>
#include <sstream>

#include <vector>

using namespace std;

class TrafficLane : public Road
{
private:
	float count = 0;
	bool stop = false;
public:
	TrafficLane(CrossingRoadGame* game, int row) : Road(game, row) {
		id = L'T';
	}
	TrafficLane(CrossingRoadGame* game, wstring dataString) : Road(game, dataString) {
		for (int i = 0; i < 14; i++)
		{
			tiles.push_back(new RoadTile(game, 8 * i, y));
		}

		id = L'T';
	}
	void Update(float fElapsedTime) {
		count -= fElapsedTime;
		if (count < 0 && !stop) {
			stop = !stop;
			count = rand() % 2 + 2;
		}
		else if (count < 0 && stop) {
			stop = !stop;
			count = rand() % 2 + 2;
		}
		if (stop) return;
		Lane::Update(fElapsedTime);
		for (int i = 0; i < vehicles.size(); i++) {
			vehicles[i]->Update(fElapsedTime);
		}
	}

	void Draw() {
		Road::Draw();
		if(stop)
			game->Fill(109, y + 1, 111, y + 3, L' ', BG_RED);
		else
			game->Fill(109, y + 1, 111, y + 3, L' ', BG_GREEN);

	}

	void SetCollisionMatrix() {
		for (int i = 0; i < vehicles.size(); i++) {
			vehicles[i]->SetCollisionMatrix();
		}
	}
};

