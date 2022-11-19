#pragma once
#include "Lane.h"
#include "Vehicle.h"
#include "GrassTile.h"
class RestLane : public Lane
{
	vector<Vehicle*> vehicles;
public:
	RestLane(CrossingRoadGame* game, int row) :Lane(game, row) {
		for (int i = 0; i < 14; i++)
		{
			tiles.push_back(new GrassTile(game, 8 * i, row));
		}
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
