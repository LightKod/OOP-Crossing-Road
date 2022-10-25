#pragma once
#include <iostream>
#include <windows.h>
#include "CrossingRoadGame.h"
using namespace std;

class Object
{
private:
	int x, y;
	int width, height;
	

public:
	int GetX();
	int GetY();

	int GetWidth();
	int GetHeight();

	virtual void SetCollisionMatrix(bool* colliderMatrix, int m_nScreenWidth, int m_nScreenHeight);

	virtual void Draw(CrossingRoadGame & game, int x, int y);

	bool CheckCollided(bool* colliderMatrix, int m_nScreenWidth, int m_nScreenHeight);

	void Clip(int& x, int& y, int m_nScreenWidth, int m_nScreenHeight);
};

