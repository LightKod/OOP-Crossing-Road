#pragma once
#include "Vehicle.h"
class Ambulance :public Vehicle
{
public:
	Ambulance(CrossingRoadGame* game, int x, int y) : Vehicle(game, x, y) {};
	void Draw();
	void AmbulanceUpdate(float fElapsedTime, bool STOP_OR_CONTINUE);
};

