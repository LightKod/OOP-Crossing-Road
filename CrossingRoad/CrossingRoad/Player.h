#pragma once
#include "CrossingRoadGame.h"
#include <windows.h>
#define FPS 0.1f
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

	virtual void CloseSound() {
		sound.CloseSound();
	}

	virtual ~Player() {};

	virtual void Update(float fElapsedTime);
	virtual void Draw();
	virtual void Standing() = 0;
	virtual void HandleAnimation(float fElapsedTime);
	virtual void SetDefaultPosition();

	virtual int GetX() final { return x; }
	virtual int GetY() final { return y; }

	virtual void SetCollisionMatrix() {}
	virtual bool CheckPlayerState();
	virtual void CheckCollided();

	virtual bool SetY(const int& _y) final;
	virtual bool SetX(const int& _x) final;
	virtual void ResetPosition() final;

	virtual bool MoveUp(const int& dY = Player::s_CellSize) = 0;
	virtual bool MoveDown(const int& dY = Player::s_CellSize) = 0;
	virtual bool MoveLeft(const int& dX = Player::s_CellSize) = 0;
	virtual bool MoveRight(const int& dX = Player::s_CellSize) = 0;

	void SetControllerInput(int index) {
		controllerIndex = index;
	}

protected:
	int counter = 0.1f;
	bool endAnimation = false;

	static const int s_CellSize;

	virtual void OnDied();
	virtual void OnMoved();

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

	
	virtual void ReadyHandle() = 0;
	virtual void LandingHandle() = 0;
	virtual void JumpHandle() = 0;

	Sound sound;
	MOVING_DIRECTION g_Dir = MOVING_DIRECTION::INVALID;
	ANIMATION_STATE g_State = ANIMATION_STATE::START;

	static bool s_CanMove;
	int frameIdx = 0;

};