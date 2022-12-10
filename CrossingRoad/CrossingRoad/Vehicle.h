#pragma once
#include "CrossingRoadGame.h"
#include <string>
#include <sstream>
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
		id = L'C';
	}
	Vehicle(CrossingRoadGame* game, int x, int y, float speed, COLOUR primary, COLOUR dark) :Object(game, x, y, width = 8, height = 8) {
		primaryColor = primary;
		darkColor = dark;
		this->speed = speed;
		id = L'C';
	}
	Vehicle(CrossingRoadGame* game, wstring dataString) : Object(game) {
		wstringstream stream(dataString);
		wstring temp;
		getline(stream, temp, L'|');
		x = stoi(temp);
		getline(stream, temp, L'|');
		y = stoi(temp);
		getline(stream, temp, L'|');
		speed = stof(temp);
		getline(stream, temp, L'|');
		primaryColor = (COLOUR)stoi(temp);
		getline(stream, temp, L'|');
		darkColor = (COLOUR)stoi(temp);

		id = L'C';
	}

	void SetRow(int row) {
		y = row;
	}

	//Viet lai ham draw de ve
	virtual void Draw();
	void Draw1();
	void Draw2();
	virtual void Update(float fElapsedTime);
	virtual void SetCollisionMatrix();

	virtual wstring GetData() {
		wstring idStr(1, id);
		wstring data = idStr + L"|" + to_wstring(x) + L"|" + to_wstring(y) + L"|" + to_wstring(speed) + L"|" + to_wstring(primaryColor) + L"|" + to_wstring(darkColor) + L"|";
		return data;
	}
};

