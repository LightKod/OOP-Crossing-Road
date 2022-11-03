#pragma once
#include "CrossingRoadGame.h"
#include <windows.h>

using namespace std;

#define VK_A 0x41
#define VK_D 0x44
#define VK_S 0x53
#define VK_W 0x57

class Player : public CrossingRoadGame::Object
{
public:
	Player(CrossingRoadGame* game, const int& x, const int& y, const int& w, const int& h) 
		: Object(game, x, y, w, h)
	{
	}
	~Player()
	{
	}

	virtual void Update(float fElapsedTime)
	{
	}

	virtual void Draw()
	{
	}

protected:
	enum class MOVING_DIRECTION
	{
		INVALID = 0,
		MOVING_UP,
		MOVING_DOWN,
		MOVING_LEFT,
		MONIG_RIGHT,
	};
	enum class ANIMATION_STATE
	{
		START = 0,
		READY,
		JUMP,
		LANDING,
		END,
	};

	void Move(int xDir, int yDir) {
		x += xDir;
		y += yDir;
	}

};