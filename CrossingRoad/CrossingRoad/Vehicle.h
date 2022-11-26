#pragma once
#include "CrossingRoadGame.h"

class Vehicle : public CrossingRoadGame::Object
{
protected:
	COLOUR primaryColor = BG_GREEN;
	COLOUR darkColor = BG_DARK_GREEN;
	//CANG NHIEU THI CANG CHAM
	float speed = 0.05f;
	float time = 0;
	wchar_t id = L'C';
public:
	//Thua ke ham constructor
	Vehicle(CrossingRoadGame* game) : CrossingRoadGame::Object(game) {}
	Vehicle(CrossingRoadGame* game, int x, int y) : CrossingRoadGame::Object(game, x, y, width = 8, height = 8) {}
	Vehicle(CrossingRoadGame* game,int x, int y, float speed) : CrossingRoadGame::Object(game, x, y, width = 8, height = 8) {
		this->speed = speed;
	}
	Vehicle(CrossingRoadGame* game, int x, int y, float speed, COLOUR primary, COLOUR dark) :Object(game, x, y, width = 8, height = 8) {
		primaryColor = primary;
		darkColor = dark;
		this->speed = speed;
	}

	//Viet lai ham draw de ve
	virtual void Draw();
	void Draw1();
	void Draw2();
	virtual void Update(float fElapsedTime);
	virtual void SetCollisionMatrix();

	virtual wstring GetData() {
		wstring idStr(1, id);
		wstring data = idStr + L"|" + to_wstring(x) + L"|" + to_wstring(speed) + L"|" + to_wstring(primaryColor) + L"|" + to_wstring(darkColor) + L"|";
		return data;
	}
};

