#include "Dog.h"

Dog::Dog(CrossingRoadGame* game) 
	: Player(game,
		game->ScreenWidth() / 8 * 2,
		game->ScreenHeight() - s_CellSize,
		s_CellSize, s_CellSize)
{
	s_CanMove = 1;
	m_OnRight = 1;
	g_Dir = MOVING_DIRECTION::INVALID;
	g_State = ANIMATION_STATE::START;
	sound.OpenBounceSound();
}

void Dog::ReadyHandle() {
	if (endAnimation) return;
	switch (g_Dir) {
	case MOVING_DIRECTION::MOVING_UP:
		this->Move(0, -3);
		break;

	case MOVING_DIRECTION::MOVING_DOWN:
		this->Move(0, 3);
		break;

	case MOVING_DIRECTION::MOVING_LEFT:
		this->Move(-3, 0);
		break;

	case MOVING_DIRECTION::MONIG_RIGHT:
		this->Move(3, 0);
		break;
	}

	Ready();
	endAnimation = true;
}
void Dog::JumpHandle() {
	if (endAnimation) return;
	switch (g_Dir) {
	case MOVING_DIRECTION::MOVING_UP:
		this->Move(0, -3);
		break;

	case MOVING_DIRECTION::MOVING_DOWN:
		this->Move(0, 3);
		break;

	case MOVING_DIRECTION::MOVING_LEFT:
		this->Move(-3, 0);
		break;

	case MOVING_DIRECTION::MONIG_RIGHT:
		this->Move(3, 0);
		break;
	}

	Jumping();
	endAnimation = true;
}
void Dog::LandingHandle() {
	if (endAnimation) return;
	switch (g_Dir) {
	case MOVING_DIRECTION::MOVING_UP:
		this->Move(0, -2);
		break;

	case MOVING_DIRECTION::MOVING_DOWN:
		this->Move(0, 2);
		break;

	case MOVING_DIRECTION::MOVING_LEFT:
		this->Move(-2, 0);
		break;

	case MOVING_DIRECTION::MONIG_RIGHT:
		this->Move(2, 0);
		break;

	default:
		break;
	}

	Landing();
	endAnimation = true;
}
// Handle moving player
bool Dog::MoveUp(const int& dY) {
	if (!s_CanMove)
		return 0;

	if ((this->GetY() - dY) >= GAME_SCREEN_LIMIT::TOP) {
		g_Dir = MOVING_DIRECTION::MOVING_UP;
		g_State = ANIMATION_STATE::READY;
		s_CanMove = false;
		return 1;
	}
	return 0;
}
bool Dog::MoveDown(const int& dY) {
	if (!s_CanMove)
		return 0;

	if ((this->GetY() + dY) < GAME_SCREEN_LIMIT::BOT) {
		g_Dir = MOVING_DIRECTION::MOVING_DOWN;
		g_State = ANIMATION_STATE::READY;
		s_CanMove = false;
		return 1;
	}
	return 0;
}
bool Dog::MoveLeft(const int& dX) {
	if (!s_CanMove)
		return 0;

	if (m_OnRight) {
		m_OnRight = !m_OnRight;
	}

	if ((this->GetX() - dX) >= GAME_SCREEN_LIMIT::LEFT) {
		g_Dir = MOVING_DIRECTION::MOVING_LEFT;
		g_State = ANIMATION_STATE::READY;
		s_CanMove = false;
		return 1;
	}
	return 0;
}
bool Dog::MoveRight(const int& dX) {
	if (!s_CanMove)
		return 0;

	if (!m_OnRight) {
		m_OnRight = !m_OnRight;
	}

	if ((this->GetX() + dX) < GAME_SCREEN_LIMIT::RIGHT) {
		g_Dir = MOVING_DIRECTION::MONIG_RIGHT;
		g_State = ANIMATION_STATE::READY;
		s_CanMove = false;
		return 1;
	}
	return 0;
}


void Dog::Standing() {
	if (m_OnRight) {
		RightStanding();
	}
	else {
		LeftStanding();
	}
}
void Dog::Ready() {
	if (m_OnRight) {
		RightOnAir1();
	}
	else {
		LeftOnAir1();
	}
}
void Dog::Jumping() {
	if (m_OnRight) {
		RightOnAir2();
	}
	else {
		LeftOnAir2();
	}
}
void Dog::Landing() {
	if (m_OnRight) {
		RightLanding();
	}
	else {
		LeftLanding();
	}
}


void Dog::RightStanding() {
	// ******************************* Vẽ thân *******************************
	// Vẽ viền
	game->DrawLine(x	, y + 3, x + 1, y + 3, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x	, y + 4, x + 1, y + 5, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 2, y + 1, x + 2, y + 4, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 3, y	   , x + 4, y + 1, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 5, y	   , x + 6, y + 1, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 6, y	+ 2, x + 7, y + 3, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 6, y	+ 5, x + 7, y + 4, 9608, FG_BLACK + BG_BLACK);

	// Vẽ lông
	game->DrawLine(x + 3, y + 1, x + 3, y + 4, 9608, FG_GREY + BG_GREY);
	game->DrawLine(x + 2, y + 5, x + 5, y + 5, 9608, FG_GREY + BG_GREY);
	game->Draw(x + 5, y + 1, 9608, FG_GREY + BG_GREY);

	// Vẽ mặt
	game->DrawLine(x + 4, y + 2, x + 4, y + 4, 9608, FG_WHITE + BG_WHITE);
	game->DrawLine(x + 5, y + 4, x + 6, y + 4, 9608, FG_WHITE + BG_WHITE);
	game->DrawLine(x + 5, y + 2, x + 6, y + 3, 9608, FG_WHITE + BG_WHITE);

	// vẽ đuôi
	game->Draw(x + 1, y + 4, 9608, FG_WHITE + BG_WHITE);

	// Vẽ mắt
	game->Draw(x + 5, y + 3, 9608, FG_DARK_GREY + BG_DARK_GREY);

	//// ******************************* Vẽ chân *******************************
	// Vẽ viền
	game->DrawLine(x + 1, y + 6, x + 1, y + 7, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 2, y + 7, x + 3, y + 6, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 4, y + 6, x + 5, y + 7, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 6, y + 6, x + 6, y + 7, 9608, FG_BLACK + BG_BLACK);

	// Vẽ lông
	game->Draw(x + 2, y + 6, 9608, FG_GREY + BG_GREY);
	game->Draw(x + 5, y + 6, 9608, FG_GREY + BG_GREY);
}
void Dog::RightOnAir1() {
	// ******************************* Vẽ thân *******************************
	// Vẽ viền
	game->DrawLine(x	, y + 2, x + 1, y + 2, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 2, y + 2, x + 2, y + 3, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x	, y + 3, x + 1, y + 4, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 1, y	+ 1, x + 2, y	 , 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 3, y	   , x + 5, y    , 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 6, y	+ 1, x + 7, y + 2, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 6, y	+ 4, x + 7, y + 3, 9608, FG_BLACK + BG_BLACK);

	// Vẽ lông
	game->DrawLine(x + 2, y + 1, x + 3, y + 1, 9608, FG_GREY + BG_GREY);
	game->DrawLine(x + 3, y + 2, x + 3, y + 3, 9608, FG_GREY + BG_GREY);
	game->DrawLine(x + 2, y + 4, x + 5, y + 4, 9608, FG_GREY + BG_GREY);

	// Vẽ mặt
	game->DrawLine(x + 4, y + 1, x + 4, y + 3, 9608, FG_WHITE + BG_WHITE);
	game->DrawLine(x + 5, y + 3, x + 6, y + 3, 9608, FG_WHITE + BG_WHITE);
	game->DrawLine(x + 5, y + 1, x + 6, y + 2, 9608, FG_WHITE + BG_WHITE);

	// vẽ đuôi
	game->Draw(x + 1, y + 3, 9608, FG_WHITE + BG_WHITE);

	// Vẽ mắt
	game->Draw(x + 5, y + 2, 9608, FG_DARK_GREY + BG_DARK_GREY);

	// ******************************* Vẽ chân *******************************
	// Vẽ viền
	game->DrawLine(x + 1, y + 5, x + 1, y + 6, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 2, y + 6, x + 3, y + 5, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 4, y + 5, x + 5, y + 5, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 6, y + 6, x + 7, y + 6, 9608, FG_BLACK + BG_BLACK);
	game->Draw(x + 7, y + 5, 9608, FG_BLACK + BG_BLACK);

	// Vẽ lông
	game->Draw(x + 2, y + 5, 9608, FG_GREY + BG_GREY);
	game->Draw(x + 6, y + 5, 9608, FG_GREY + BG_GREY);
}
void Dog::RightOnAir2() {
	// ******************************* Vẽ thân *******************************
	// Vẽ viền
	game->DrawLine(x, y + 2, x + 1, y + 2, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 2, y + 2, x + 2, y + 3, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x, y + 3, x + 1, y + 4, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 1, y + 1, x + 2, y, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 3, y, x + 5, y, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 6, y + 1, x + 7, y + 2, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 6, y + 4, x + 7, y + 3, 9608, FG_BLACK + BG_BLACK);

	// Vẽ lông
	game->DrawLine(x + 2, y + 1, x + 3, y + 1, 9608, FG_GREY + BG_GREY);
	game->DrawLine(x + 3, y + 2, x + 3, y + 3, 9608, FG_GREY + BG_GREY);
	game->DrawLine(x + 2, y + 4, x + 5, y + 4, 9608, FG_GREY + BG_GREY);

	// Vẽ mặt
	game->DrawLine(x + 4, y + 1, x + 4, y + 3, 9608, FG_WHITE + BG_WHITE);
	game->DrawLine(x + 5, y + 3, x + 6, y + 3, 9608, FG_WHITE + BG_WHITE);
	game->DrawLine(x + 5, y + 1, x + 6, y + 2, 9608, FG_WHITE + BG_WHITE);

	// vẽ đuôi
	game->Draw(x + 1, y + 3, 9608, FG_WHITE + BG_WHITE);

	// Vẽ mắt
	game->Draw(x + 5, y + 2, 9608, FG_DARK_GREY + BG_DARK_GREY);

	// ******************************* Vẽ chân *******************************
	// Vẽ viền
	game->DrawLine(x	, y + 5, x	  , y + 6, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 1, y + 6, x + 2, y + 5, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 3, y + 5, x + 5, y + 5, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 6, y + 6, x + 7, y + 6, 9608, FG_BLACK + BG_BLACK);
	game->Draw(x + 7, y + 5, 9608, FG_BLACK + BG_BLACK);

	// Vẽ lông
	game->Draw(x + 1, y + 5, 9608, FG_GREY + BG_GREY);
	game->Draw(x + 6, y + 5, 9608, FG_GREY + BG_GREY);
}
void Dog::RightLanding() {
	// ******************************* Vẽ thân *******************************
// Vẽ viền
	game->DrawLine(x, y + 3, x + 1, y + 3, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x, y + 4, x + 1, y + 5, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 2, y + 1, x + 2, y + 4, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 3, y, x + 4, y + 1, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 5, y, x + 6, y + 1, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 6, y + 2, x + 7, y + 3, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 6, y + 5, x + 7, y + 4, 9608, FG_BLACK + BG_BLACK);

	// Vẽ lông
	game->DrawLine(x + 3, y + 1, x + 3, y + 4, 9608, FG_GREY + BG_GREY);
	game->DrawLine(x + 2, y + 5, x + 5, y + 5, 9608, FG_GREY + BG_GREY);
	game->Draw(x + 5, y + 1, 9608, FG_GREY + BG_GREY);

	// Vẽ mặt
	game->DrawLine(x + 4, y + 2, x + 4, y + 4, 9608, FG_WHITE + BG_WHITE);
	game->DrawLine(x + 5, y + 4, x + 6, y + 4, 9608, FG_WHITE + BG_WHITE);
	game->DrawLine(x + 5, y + 2, x + 6, y + 3, 9608, FG_WHITE + BG_WHITE);

	// vẽ đuôi
	game->Draw(x + 1, y + 4, 9608, FG_WHITE + BG_WHITE);

	// Vẽ mắt
	game->Draw(x + 5, y + 3, 9608, FG_DARK_GREY + BG_DARK_GREY);

	//// ******************************* Vẽ chân *******************************
	// Vẽ viền
	game->DrawLine(x	, y + 6, x	  , y + 7, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 1, y + 7, x + 2, y + 6, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 3, y + 6, x + 4, y + 6, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 5, y + 7, x + 6, y + 7, 9608, FG_BLACK + BG_BLACK);
	game->Draw(x + 6, y + 6, 9608, FG_BLACK + BG_BLACK);

	// Vẽ lông
	game->Draw(x + 1, y + 6, 9608, FG_GREY + BG_GREY);
	game->Draw(x + 5, y + 6, 9608, FG_GREY + BG_GREY);
}

void Dog::LeftStanding() {
	// ******************************* Vẽ thân *******************************
	// Vẽ viền
	game->DrawLine(x	, y + 4, x + 1, y + 5, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x	, y + 3, x + 1, y + 2, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 1, y + 1, x + 2, y	 , 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 3, y + 1, x + 4, y	 , 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 5, y + 1, x + 5, y + 4, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 6, y + 3, x + 7, y + 3, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 6, y + 5, x + 7, y + 4, 9608, FG_BLACK + BG_BLACK);

	// Vẽ lông
	game->DrawLine(x + 4, y + 1, x + 4, y + 4, 9608, FG_GREY + BG_GREY);
	game->DrawLine(x + 2, y + 5, x + 5, y + 5, 9608, FG_GREY + BG_GREY);
	game->Draw(x + 2, y + 1, 9608, FG_GREY + BG_GREY);

	// Vẽ mặt
	game->DrawLine(x + 1, y + 3, x + 2, y + 2, 9608, FG_WHITE + BG_WHITE);
	game->DrawLine(x + 1, y + 4, x + 3, y + 4, 9608, FG_WHITE + BG_WHITE);
	game->DrawLine(x + 3, y + 2, x + 3, y + 3, 9608, FG_WHITE + BG_WHITE);

	// vẽ đuôi
	game->Draw(x + 6, y + 4, 9608, FG_WHITE + BG_WHITE);

	// Vẽ mắt
	game->Draw(x + 2, y + 3, 9608, FG_DARK_GREY + BG_DARK_GREY);

	//// ******************************* Vẽ chân *******************************
	// Vẽ viền
	game->DrawLine(x + 1, y + 6, x + 1, y + 7, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 2, y + 7, x + 3, y + 6, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 4, y + 6, x + 5, y + 7, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 6, y + 6, x + 6, y + 7, 9608, FG_BLACK + BG_BLACK);

	// Vẽ lông
	game->Draw(x + 2, y + 6, 9608, FG_GREY + BG_GREY);
	game->Draw(x + 5, y + 6, 9608, FG_GREY + BG_GREY);
}
void Dog::LeftOnAir1() {
	// ******************************* Vẽ thân *******************************
	// Vẽ viền
	game->DrawLine(x	, y + 3, x + 1, y + 4, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x	, y + 2, x + 1, y + 1, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 2, y	   , x + 5, y	 , 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 6, y	+ 1, x + 6, y + 2, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 5, y	+ 2, x + 5, y + 3, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 7, y	+ 2, x + 7, y + 3, 9608, FG_BLACK + BG_BLACK);
	game->Draw(x + 6, y + 4, 9608, FG_BLACK + BG_BLACK);

	// Vẽ lông
	game->DrawLine(x + 4, y + 1, x + 4, y + 3, 9608, FG_GREY + BG_GREY);
	game->DrawLine(x + 2, y + 4, x + 5, y + 4, 9608, FG_GREY + BG_GREY);
	game->Draw(x + 5, y + 1, 9608, FG_GREY + BG_GREY);

	// Vẽ mặt
	game->DrawLine(x + 3, y + 1, x + 3, y + 3, 9608, FG_WHITE + BG_WHITE);
	game->DrawLine(x + 1, y + 3, x + 2, y + 3, 9608, FG_WHITE + BG_WHITE);
	game->DrawLine(x + 1, y + 2, x + 2, y + 1, 9608, FG_WHITE + BG_WHITE);

	// vẽ đuôi
	game->Draw(x + 6, y + 3, 9608, FG_WHITE + BG_WHITE);

	// Vẽ mắt
	game->Draw(x + 2, y + 2, 9608, FG_DARK_GREY + BG_DARK_GREY);

	// ******************************* Vẽ chân *******************************
	// Vẽ viền
	game->DrawLine(x	, y + 5, x	  , y + 6, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 1, y + 6, x + 2, y + 5, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 3, y + 5, x + 4, y + 5, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 5, y + 6, x + 6, y + 6, 9608, FG_BLACK + BG_BLACK);
	game->Draw(x + 6, y + 5, 9608, FG_BLACK + BG_BLACK);

	// Vẽ lông
	game->Draw(x + 1, y + 5, 9608, FG_GREY + BG_GREY);
	game->Draw(x + 5, y + 5, 9608, FG_GREY + BG_GREY);
}
void Dog::LeftOnAir2() {
	// ******************************* Vẽ thân *******************************
	// Vẽ viền
	game->DrawLine(x, y + 3, x + 1, y + 4, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x, y + 2, x + 1, y + 1, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 2, y, x + 5, y, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 6, y + 1, x + 6, y + 2, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 5, y + 2, x + 5, y + 3, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 7, y + 2, x + 7, y + 3, 9608, FG_BLACK + BG_BLACK);
	game->Draw(x + 6, y + 4, 9608, FG_BLACK + BG_BLACK);

	// Vẽ lông
	game->DrawLine(x + 4, y + 1, x + 4, y + 3, 9608, FG_GREY + BG_GREY);
	game->DrawLine(x + 2, y + 4, x + 5, y + 4, 9608, FG_GREY + BG_GREY);
	game->Draw(x + 5, y + 1, 9608, FG_GREY + BG_GREY);

	// Vẽ mặt
	game->DrawLine(x + 3, y + 1, x + 3, y + 3, 9608, FG_WHITE + BG_WHITE);
	game->DrawLine(x + 1, y + 3, x + 2, y + 3, 9608, FG_WHITE + BG_WHITE);
	game->DrawLine(x + 1, y + 2, x + 2, y + 1, 9608, FG_WHITE + BG_WHITE);

	// vẽ đuôi
	game->Draw(x + 6, y + 3, 9608, FG_WHITE + BG_WHITE);

	// Vẽ mắt
	game->Draw(x + 2, y + 2, 9608, FG_DARK_GREY + BG_DARK_GREY);

	// ******************************* Vẽ chân *******************************
	// Vẽ viền
	game->DrawLine(x, y + 5, x, y + 6, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 1, y + 6, x + 2, y + 5, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 3, y + 5, x + 5, y + 5, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 6, y + 6, x + 7, y + 6, 9608, FG_BLACK + BG_BLACK);
	game->Draw(x + 7, y + 5, 9608, FG_BLACK + BG_BLACK);

	// Vẽ lông
	game->Draw(x + 1, y + 5, 9608, FG_GREY + BG_GREY);
	game->Draw(x + 6, y + 5, 9608, FG_GREY + BG_GREY);
}
void Dog::LeftLanding() {
	// ******************************* Vẽ thân *******************************
	// Vẽ viền
	game->DrawLine(x, y + 4, x + 1, y + 5, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x, y + 3, x + 1, y + 2, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 1, y + 1, x + 2, y, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 3, y + 1, x + 4, y, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 5, y + 1, x + 5, y + 4, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 6, y + 3, x + 7, y + 3, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 6, y + 5, x + 7, y + 4, 9608, FG_BLACK + BG_BLACK);

	// Vẽ lông
	game->DrawLine(x + 4, y + 1, x + 4, y + 4, 9608, FG_GREY + BG_GREY);
	game->DrawLine(x + 2, y + 5, x + 5, y + 5, 9608, FG_GREY + BG_GREY);
	game->Draw(x + 2, y + 1, 9608, FG_GREY + BG_GREY);

	// Vẽ mặt
	game->DrawLine(x + 1, y + 3, x + 2, y + 2, 9608, FG_WHITE + BG_WHITE);
	game->DrawLine(x + 1, y + 4, x + 3, y + 4, 9608, FG_WHITE + BG_WHITE);
	game->DrawLine(x + 3, y + 2, x + 3, y + 3, 9608, FG_WHITE + BG_WHITE);

	// vẽ đuôi
	game->Draw(x + 6, y + 4, 9608, FG_WHITE + BG_WHITE);

	// Vẽ mắt
	game->Draw(x + 2, y + 3, 9608, FG_DARK_GREY + BG_DARK_GREY);

	//// ******************************* Vẽ chân *******************************
	// Vẽ viền
	game->DrawLine(x + 1, y + 6, x + 1, y + 7, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 2, y + 7, x + 3, y + 6, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 4, y + 6, x + 5, y + 6, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 6, y + 7, x + 7, y + 7, 9608, FG_BLACK + BG_BLACK);
	game->Draw(x + 7, y + 6, 9608, FG_BLACK + BG_BLACK);

	// Vẽ lông
	game->Draw(x + 2, y + 6, 9608, FG_GREY + BG_GREY);
	game->Draw(x + 6, y + 6, 9608, FG_GREY + BG_GREY);
}
