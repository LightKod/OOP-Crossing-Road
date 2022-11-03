#pragma once
#include "CrossingRoadGame.h"

class Vehicle : public CrossingRoadGame::Object
{
private:
	COLOUR primaryColor = BG_GREEN;
	COLOUR darkColor = BG_DARK_GREEN;
	//CANG NHIEU THI CANG CHAM
	float speed = 0.05f;
	float time = 0;
public:
	//Thua ke ham constructor
	Vehicle(CrossingRoadGame* game) : CrossingRoadGame::Object(game) {}
	Vehicle(CrossingRoadGame* game,int x, int y, int width, int height) : CrossingRoadGame::Object(game, x, y, width, height) {}
	Vehicle(CrossingRoadGame* game,int x, int y, int width, int height, float speed) : CrossingRoadGame::Object(game, x, y, width, height) {
		this->speed = speed;
	}
	Vehicle(CrossingRoadGame* game, int x, int y, int width, int height, float speed, COLOUR primary, COLOUR dark) :Object(game, x, y, width, height) {
		primaryColor = primary;
		darkColor = dark;
		this->speed = speed;
	}

	//Viet lai ham draw de ve
	virtual void Draw();
	virtual void Update(float fElapsedTime);
};

