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

		for (int i = 0; i < 7; i++)
		{
			tiles.push_back(new RoadTile(game, 16 * i, row));
		}
		vehicles.push_back(new Vehicle(game, randomValue, row, speed));
		vehicles.push_back(new Vehicle(game, randomValue1, row,speed));
		vehicles.push_back(new Vehicle(game, randomValue2, row,speed));

		random = rand() % 3;
		if (random == 1)
		{
			speed = 0.07f;
		}
		else if (random == 2)
		{
			speed = -0.09f;
		}
		else
		{
			speed = 0.05f;
		}
		randomValue = rand() % 20;
		randomValue1 = rand() % 30 + 40;
		randomValue2 = rand() % 22 + 90;
		vehicles.push_back(new Vehicle(game, randomValue, row + 8,speed));
		vehicles.push_back(new Vehicle(game, randomValue1, row + 8,speed));
		vehicles.push_back(new Vehicle(game, randomValue2, row + 8,speed));
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

