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
private:
	vector<Vehicle*> vehicles;
public:
	Road(CrossingRoadGame* game, int row) :Lane(game, row) {
		static unsigned int seed = time(NULL);
		srand(seed++);
		int randomValue = rand() % 20;
		int randomValue1 = rand() % 30 + 40;
		int randomValue2 = rand() % 22 + 90;
		for (int i = 0; i < 7; i++)
		{
			tiles.push_back(new RoadTile(game, 16 * i, row));
		}

		vehicles.push_back(new Vehicle(game, randomValue, row));
		vehicles.push_back(new Vehicle(game,randomValue1, row));
		vehicles.push_back(new Vehicle(game,randomValue2, row));


		randomValue = rand() % 20;
		randomValue1 = rand() % 30 + 40;
		randomValue2 = rand() % 22 + 90;
		vehicles.push_back(new Vehicle(game, randomValue, row + 8));
		vehicles.push_back(new Vehicle(game, randomValue1, row + 8));
		vehicles.push_back(new Vehicle(game, randomValue2, row + 8));
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

