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
		id = L'G';
	}
	RestLane(CrossingRoadGame* game, wstring dataString) : Lane(game, dataString) {
		for (int i = 0; i < 14; i++)
		{
			tiles.push_back(new GrassTile(game, 8 * i, y));
		}
		id = L'G';
	}
	void Draw() {
		Lane::Draw();
	}
	virtual void SetCollisionMatrix() {
		for (int i = 0; i < vehicles.size(); i++) {
			vehicles[i]->SetCollisionMatrix();
		}
	}
};
