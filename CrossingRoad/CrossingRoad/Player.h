#pragma once
#include "CrossingRoadGame.h"
#include <windows.h>

using namespace std;

class Player : public CrossingRoadGame::Object {
private:
	int controllerIndex = 0;
public:
	enum class PLAYER_STATE {
		ALIVE,
		DEAD,
	};

	PLAYER_STATE p_State = PLAYER_STATE::ALIVE;

	Player(CrossingRoadGame* game, const int& x, const int& y, const int& w, const int& h)
		: Object(game, x, y, w, h)
	{
		controllerIndex = 0;
	}

	virtual ~Player() {};
	virtual void Standing() = 0;

	virtual void Update(float fElapsedTime);
	virtual void Draw() = 0;
	virtual void SetDefaultPosition() = 0;

	virtual int GetX() final { return x; }
	virtual int GetY() final { return y; }

	virtual void SetCollisionMatrix() {}
	virtual bool CheckPlayerState();
	virtual void CheckCollided();

	virtual bool SetY(const int& _y) final;
	virtual bool SetX(const int& _x) final;
	virtual void ResetPosition() final;

	virtual void CloseSound() = 0;

	virtual bool MoveUp(const int& dY = Player::s_CellSize) = 0;
	virtual bool MoveDown(const int& dY = Player::s_CellSize) = 0;
	virtual bool MoveLeft(const int& dX = Player::s_CellSize) = 0;
	virtual bool MoveRight(const int& dX = Player::s_CellSize) = 0;

	void SetControllerInput(int index) {
		controllerIndex = index;
	}

protected:
	static const int s_CellSize;

	virtual void OnDied() {}
	virtual void OnMoved() {}

	enum GAME_SCREEN_LIMIT : short {
		TOP = 0,
		BOT = 96,
		LEFT = 0,
		RIGHT = 106,
	};
	enum class MOVING_DIRECTION {
		INVALID = 0,
		MOVING_UP,
		MOVING_DOWN,
		MOVING_LEFT,
		MONIG_RIGHT,
	};
	virtual void Move(int xDir, int yDir) final;
	enum class ANIMATION_STATE {
		START = 0,
		READY = 1,
		JUMP  = 2,
		LANDING=3,
		END	  = 4,
	};

};