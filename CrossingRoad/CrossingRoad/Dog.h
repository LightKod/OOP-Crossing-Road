#pragma once
#ifndef _DOG_H_
#define _DOG_H_
#include "Player.h"

class Dog : public Player {
public:
	Dog(CrossingRoadGame* game);

	virtual void Standing();
	// Handle moving player
	virtual bool MoveUp(const int& dY = Player::s_CellSize);
	virtual bool MoveDown(const int& dY = Player::s_CellSize);
	virtual bool MoveLeft(const int& dX = Player::s_CellSize);
	virtual bool MoveRight(const int& dX = Player::s_CellSize);

private:

	virtual void ReadyHandle();
	virtual void LandingHandle();
	virtual void JumpHandle();

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

	bool m_OnRight = 1;
};

#endif // !_DOG_H_
