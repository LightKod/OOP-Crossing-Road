// CrossingRoad.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "CrossingRoadGame.h"
#include "io.h"
#include "fcntl.h"

int main()
{
	CrossingRoadGame game;
	game.ConstructConsole(160, 96, 8, 8);// 160, 96, 8, 8
	game.Start();
	system("pause>0");
}
