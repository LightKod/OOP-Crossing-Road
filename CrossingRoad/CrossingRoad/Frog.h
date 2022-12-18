#pragma once
#ifndef _FROG_H_
#define _FROG_H_
#include "Player.h"

class Frog : public Player {
public:
	Frog(CrossingRoadGame* game);
	virtual ~Frog();
	// Handle moving player
	virtual bool MoveUp(const int& dY = Player::s_CellSize);
	virtual bool MoveDown(const int& dY = Player::s_CellSize);
	virtual bool MoveLeft(const int& dX = Player::s_CellSize);
	virtual bool MoveRight(const int& dX = Player::s_CellSize);
	virtual void Standing();

private:
	virtual void SetDefaultPosition();

	virtual void ReadyHandle();
	virtual void LandingHandle();
	virtual void JumpHandle();

	virtual void ReadyJumpAndLanding();
	virtual void Jumping();
	
private:
	olcSprite* sprAvatar = nullptr;

};

#endif // !_FROG_H_


