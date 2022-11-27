#pragma once
#ifndef _DOG_H_
#define _DOG_H_
#include "Player.h"

class Dog : public Player {
public:
	Dog(CrossingRoadGame* game);

	virtual void Update(float fElapsedTime);
	virtual void Draw();

	// Handle moving player
	virtual bool MoveUp(const int& dY = Player::s_CellSize);
	virtual bool MoveDown(const int& dY = Player::s_CellSize);
	virtual bool MoveLeft(const int& dX = Player::s_CellSize);
	virtual bool MoveRight(const int& dX = Player::s_CellSize);

private:
	virtual void ReadyHandle();
	virtual void LandingHandle();
	virtual void JumpHandle();
	
	
	virtual void CheckCollided();

	virtual void Standing();
	virtual void Ready();
	virtual void Jumping();
	virtual void Landing();

	virtual void RightStanding();
	virtual void RightOnAir1();
	virtual void RightOnAir2();
	virtual void RightLanding();

	virtual void LeftStanding();
	virtual void LeftOnAir1();
	virtual void LeftOnAir2();
	virtual void LeftLanding();

	MOVING_DIRECTION g_Dir = MOVING_DIRECTION::INVALID;
	ANIMATION_STATE g_State = ANIMATION_STATE::START;
	bool s_CanMove = 1;
	bool m_OnRight = 1;

};

#endif // !_DOG_H_
