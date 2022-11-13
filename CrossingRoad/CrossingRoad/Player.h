#pragma once
#include "CrossingRoadGame.h"
#include <windows.h>

using namespace std;

class Player : public CrossingRoadGame::Object
{

private:
public:
	enum class PLAYER_STATE
	{
		ALIVE,
		DEAD,
	};
	PLAYER_STATE p_State = PLAYER_STATE::ALIVE;
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
	int GetX()
	{
		return x;
	}
	int GetY()
	{
		return y;
	}
	virtual void SetCollisionMatrix() {}
	bool CheckPlayerState()
	{
		if (p_State == PLAYER_STATE::DEAD)
			return true;
		return false;
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