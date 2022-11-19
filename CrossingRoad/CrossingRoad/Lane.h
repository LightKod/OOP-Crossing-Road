#pragma once
#include "Tile.h"
#include "Vehicle.h"
#include <vector>

using namespace std;

class Lane : public CrossingRoadGame::Object
{
protected:
	wchar_t id = L' ';
	vector<Tile*> tiles;
	vector<Vehicle*> vehicles;

public:
	Lane(CrossingRoadGame*game, int row) :Object(game, x = 0, y = row, width = 112, height = 16) {};

	virtual void Draw() {
		for (int i = 0; i < tiles.size(); i++) {
			tiles[i]->Draw();
		}
	}

	virtual void Update(float fElapsedTime) {
		for (int i = 0; i < tiles.size(); i++) {
			tiles[i]->Update(fElapsedTime);
		}
	}

	virtual void SetCollisionMatrix() {}

	wchar_t GetLaneID() {
		return id;
	}

	virtual wstring GetData() {
		wstring idStr(1, id);
		wstring data = idStr + L"|" + to_wstring(y) + L"|\n" + to_wstring(vehicles.size()) + L"\n";
		for (int i = 0; i < vehicles.size(); i++) {
			data += vehicles[i]->GetData()+ L"@\n";
		}
		data += L"#\n";
		return data;
	}	

	~Lane() {
		while (!tiles.empty()) {
			Tile* t = tiles.back();
			tiles.pop_back();
			delete t;
		}

		while (!vehicles.empty()) {
			Vehicle* v = vehicles.back();
			vehicles.pop_back();
			delete v;
		}
	}
};

