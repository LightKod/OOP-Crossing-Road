#pragma once
#ifndef _FROG_H_
#define _FROG_H_
#include "Player.h"

class Frog : public Player {
public:
	Frog(CrossingRoadGame* game);
	virtual ~Frog();

	virtual void Update(float fElapsedTime);
	virtual void Draw();

protected:
	virtual void SetDefaultPosition();

	virtual void ReadyHandle();
	virtual void LandingHandle();
	virtual void JumpHandle();

	virtual void CheckCollided();

	virtual void Standing();
	virtual void ReadyJumpAndLanding();
	virtual void Jumping();

	// Handle moving player
	virtual bool MoveUp(const int& dY = Player::s_CellSize);
	virtual bool MoveDown(const int& dY = Player::s_CellSize);
	virtual bool MoveLeft(const int& dX = Player::s_CellSize);
	virtual bool MoveRight(const int& dX = Player::s_CellSize);

private:
	olcSprite* sprAvatar = nullptr;
	MOVING_DIRECTION g_Dir = MOVING_DIRECTION::INVALID;
	ANIMATION_STATE g_State = ANIMATION_STATE::START;
	Sound frogsound;

	static bool s_CanMove;
	int frameIdx = 0;

};

#endif // !_FROG_H_


