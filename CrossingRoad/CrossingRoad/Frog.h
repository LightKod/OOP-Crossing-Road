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
	virtual void CheckCollided();
	virtual void JumpHandle();

	virtual void Standing();
	virtual void ReadyJumpAndLanding();
	virtual void Jumping();

	// Handle moving player
	virtual bool MoveUp(const int& dY = s_CellSize);
	virtual bool MoveDown(const int& dY = s_CellSize);
	virtual bool MoveLeft(const int& dX = s_CellSize);
	virtual bool MoveRight(const int& dX = s_CellSize);

private:
	olcSprite* sprAvatar = nullptr;
	MOVING_DIRECTION g_Dir = MOVING_DIRECTION::INVALID;
	ANIMATION_STATE g_State = ANIMATION_STATE::START;
	Sound frogsound;

	static const int s_CellSize;
	static bool s_CanMove;

};

#endif // !_FROG_H_


