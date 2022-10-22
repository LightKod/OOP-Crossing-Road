#pragma once
#include <iostream>
#include <windows.h>

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

	virtual void Draw(CHAR_INFO* m_bufScreen);

	bool CheckCollided(bool* colliderMatrix, int m_nScreenWidth, int m_nScreenHeight);

	void Clip(int& x, int& y, int m_nScreenWidth, int m_nScreenHeight);
};

