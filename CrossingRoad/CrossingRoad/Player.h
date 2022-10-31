#pragma once
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "Object.h"

#define VK_A 0x41
#define VK_D 0x44
#define VK_S 0x53
#define VK_W 0x57

class Player : public Object
{
public:
	Player(CrossingRoadGame& game, const int& x, const int& y, const int& w, const int& h) 
		: Object(x, y, w, h)
	{
	}
	~Player()
	{
	}

	virtual void Update(CrossingRoadGame& game, float fElapsedTime)
	{
	}

	virtual void Draw(CrossingRoadGame& game)
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

private:

};


#endif // !_PLAYER_H_