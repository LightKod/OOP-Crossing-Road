#pragma once
#include "Object.h"

class Vehicle : public Object
{
private: 
	COLOUR primaryColor = BG_GREEN;
	COLOUR darkColor = BG_DARK_GREEN;
	//CANG NHIEU THI CANG CHAM
	float speed = 0.05f;
	float time = 0;
public:
	//Thua ke ham constructor
	Vehicle() : Object() {}
	Vehicle(int x, int y, int width, int height) :Object( x, y, width, height) {}
	Vehicle(int x, int y, int width, int height, float speed) :Object( x, y, width, height) {
		this->speed = speed;
	}
	Vehicle( int x, int y, int width, int height,float speed, COLOUR primary, COLOUR dark) :Object( x, y, width, height) {
		primaryColor = primary;
		darkColor = dark;
		this->speed = speed;
	}

	//Viet lai ham draw de ve
	virtual void Draw(CrossingRoadGame& game);
	virtual void Update(CrossingRoadGame& game, float fElapsedTime);
};

