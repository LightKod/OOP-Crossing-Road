#pragma once
#include "Lane.h"
#include "Vehicle.h"
#include "GrassTile.h"
class RestLane : public Lane
{
	vector<Vehicle*> vehicles;
public:
	RestLane(CrossingRoadGame* game, int row) :Lane(game, row) {
		float speed = 0.0f;
		for (int i = 0; i < 14; i++)
		{
			tiles.push_back(new GrassTile(game, 8 * i, row));
		}

		int randomValue = rand() % 20;
		int randomValue1 = rand() % 30 + 40 ;
		int randomValue2 = rand() % 22 + 90 -8;
		vehicles.push_back(new Vehicle(game, randomValue, row, speed));
		vehicles.push_back(new Vehicle(game, randomValue1, row, speed));
		vehicles.push_back(new Vehicle(game, randomValue2, row, speed));
	}
	void Draw() {
		Lane::Draw();
		for (int i = 0; i < vehicles.size(); i++) {
			vehicles[i]->DrawTree();
		}
	}
	virtual void SetCollisionMatrix() {
		for (int i = 0; i < vehicles.size(); i++) {
			vehicles[i]->SetCollisionMatrix();
		}
	}
};
