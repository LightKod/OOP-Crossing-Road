#include "Object.h"



int Object::GetX() {return x;}
int Object::GetY() {return y;}
int Object::GetWidth() { return width; }
int Object::GetHeight() { return height; }
void Object::SetCollisionMatrix(bool* colliderMatrix, int m_nScreenWidth, int m_nScreenHeight) {
	for (int i = 0; i < x + width; i++)
	{
		for (int j = 0; j < y + height; j++)
		{
			colliderMatrix[j * m_nScreenWidth + i] = true;
		}
	}
}

void Object::Draw(CrossingRoadGame &game, int x, int y) {

}

bool Object::CheckCollided(bool* colliderMatrix, int m_nScreenWidth, int m_nScreenHeight) {
	int xTemp = x;
	int yTemp = y;

	Clip(xTemp, yTemp, m_nScreenWidth, m_nScreenHeight);
	bool tl = colliderMatrix[yTemp * m_nScreenWidth + xTemp];

	xTemp = x + width;
	yTemp = y;
	Clip(xTemp, yTemp, m_nScreenWidth, m_nScreenHeight);
	bool tr = colliderMatrix[yTemp * m_nScreenWidth + xTemp];

	xTemp = x;
	yTemp = y + height;
	Clip(xTemp, yTemp, m_nScreenWidth, m_nScreenHeight);
	bool bl = colliderMatrix[yTemp * m_nScreenWidth + xTemp];

	xTemp = x + width;	
	yTemp = y + height;
	Clip(xTemp, yTemp, m_nScreenWidth, m_nScreenHeight);
	bool br = colliderMatrix[yTemp * m_nScreenWidth + xTemp];

	return tl || tr || bl || br;
}

void Object::Clip(int& x, int& y, int m_nScreenWidth, int m_nScreenHeight)
{
	if (x < 0) x = 0;
	if (x >= m_nScreenWidth) x = m_nScreenWidth;
	if (y < 0) y = 0;
	if (y >= m_nScreenHeight) y = m_nScreenHeight;
}