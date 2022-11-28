#pragma once
#include "Vehicle.h"
class Ambulance :public Vehicle
{
public:
	Ambulance(CrossingRoadGame* game, int x, int y, float speed) : Vehicle(game, x, y, speed) {};
	void Draw();
	void AmbulanceUpdate(float fElapsedTime, bool STOP_OR_CONTINUE);
};

