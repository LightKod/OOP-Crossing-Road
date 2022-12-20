#pragma once
#include "Tile.h"
#include "Vehicle.h"
#include "Duck.h"
#include <vector>
#include <string>
#include <sstream>
using namespace std;

class Lane : public CrossingRoadGame::Object
{
protected:
	wchar_t id = L' ';
	vector<Tile*> tiles;
	vector<Vehicle*> vehicles;

public:
	Lane(CrossingRoadGame*game, int row) :Object(game, x = 0, y = row, width = 112, height = 8) {};
	Lane(CrossingRoadGame* game, wstring dataString) : Object(game, x = 0, y = 0, width = 112, height = 8) {
		wstringstream stream(dataString);
		wstring temp;
		wstring vehicleData;
		getline(stream, temp);
		y = stoi(temp);
		getline(stream, temp);
		int vehicleAmount = stoi(temp);
		for (int i = 0; i < vehicleAmount; i++)
		{
			getline(stream, temp, L'|');
			wchar_t vehicleId = temp[0];
			getline(stream, vehicleData, L'@');
			switch (vehicleId)
			{
			case L'C':
				vehicles.push_back(new Vehicle(game, vehicleData));
				break;
			case L'D':
				vehicles.push_back(new Duck(game, vehicleData));
				break;
			default:
				break;
			}
			getline(stream, temp);
		}
	}

	virtual void Draw() {
		for (int i = 0; i < tiles.size(); i++) {
			tiles[i]->Draw();
		}
		for (int i = 0; i < vehicles.size(); i++) {
			vehicles[i]->Draw();
		}
	}

	virtual void Update(float fElapsedTime) {
		for (int i = 0; i < tiles.size(); i++) {
			tiles[i]->Update(fElapsedTime);
		}
		for (int i = 0; i < vehicles.size(); i++) {
			vehicles[i]->Update(fElapsedTime);
		}
	}

	virtual void SetCollisionMatrix() {}

	void SetRow(int row) {
		y = row;
		for (int i = 0; i < vehicles.size(); i++)
		{
			vehicles[i]->SetRow(row);
		}
		for (int i = 0; i < tiles.size(); i++)
		{
			tiles[i]->SetRow(row);
		}
	}

	wchar_t GetLaneID() {
		return id;
	}

	virtual wstring GetData() {
		wstring idStr(1, id);
		wstring data = idStr + L"\n" + to_wstring(y) + L"\n" + to_wstring(vehicles.size()) + L"\n";
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

