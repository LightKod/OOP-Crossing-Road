#pragma once
#include <iostream>
#include <windows.h>
#include "CrossingRoadGame.h"
using namespace std;

class Object
{
protected:
	int x, y;
	int width, height;

public:
	//Contructors de Object tuong tac duoc void Game
	Object();
	Object(int, int, int, int);
	Object(int x, int y);

	//Getters
	int GetX();
	int GetY();
	int GetWidth();
	int GetHeight();

	//Di chuyen theo huong
	bool Move(int xDir, int yDir);
	//Set vi tri
	bool SetPosition(int x, int y);


	//Hai ham` ve voi Set Collision
	//Minh` se edit chu yeu 3 ham nay de ve ra Object (vi du trong class Tile)
	//Dung de update moi frame
	virtual void Update(CrossingRoadGame& game, float fElapsedTime);
	//Set cai ma tran collision
	virtual void SetCollisionMatrix(CrossingRoadGame& game);
	//Ve ra man hinh tuy` vi tri x, y
	virtual void Draw(CrossingRoadGame& game);

	//Check coi Object co dang de` len CollisionMatrix ko
	bool CheckCollided(CrossingRoadGame& game);
};

