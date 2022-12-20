#include "Player.h"

const int Player::s_CellSize = 8;

bool Player::CheckPlayerState() {
	if (p_State == PLAYER_STATE::DEAD)
		return true;
	return false;
}

void Player::Draw() {
	switch (g_State) {
	case ANIMATION_STATE::START:
		Standing();
		if (p_State == PLAYER_STATE::ALIVE)
			s_CanMove = 1;
		return;

	case ANIMATION_STATE::READY:
		ReadyHandle();
		break;

	case ANIMATION_STATE::JUMP:
		JumpHandle();
		break;
			
	case ANIMATION_STATE::LANDING:
		LandingHandle();
		break;

	case ANIMATION_STATE::END:
		Standing();
		break;

	default:
		Standing();
		return;
	}
}

void Player::Update(float fElapsedTime) {
	HandleAnimation(fElapsedTime);
	if (controllerIndex == 0) {
		if (game->m_keys[VK_W].bPressed) {
			if (this->MoveUp())
				OnMoved();
		}
		if (game->m_keys[VK_S].bPressed) {
			if (this->MoveDown())
				OnMoved();
		}
		if (game->m_keys[VK_A].bPressed) {
			if (this->MoveLeft())
				OnMoved();
		}
		if (game->m_keys[VK_D].bPressed) {
			if (this->MoveRight())
				OnMoved();
		}
	}
	else {
		if (game->m_keys[VK_UP].bPressed) {
			if (this->MoveUp())
				OnMoved();
		}
		if (game->m_keys[VK_DOWN].bPressed) {
			if (this->MoveDown())
				OnMoved();
		}
		if (game->m_keys[VK_LEFT].bPressed) {
			if (this->MoveLeft())
				OnMoved();
		}
		if (game->m_keys[VK_RIGHT].bPressed) {
			if (this->MoveRight())
				OnMoved();
		}
	}
	

	CheckCollided();
}

void Player::HandleAnimation(float fElapsedTime) {
	if (g_State == ANIMATION_STATE::START) return;
	counter -= fElapsedTime;
	if (counter <= 0) {
		if (!endAnimation) return;
		endAnimation = false;
		switch (g_State) {
		case ANIMATION_STATE::READY:
			g_State = ANIMATION_STATE::JUMP;
			break;
		case ANIMATION_STATE::JUMP:
			g_State = ANIMATION_STATE::LANDING;
			break;

		case ANIMATION_STATE::LANDING:
			g_State = ANIMATION_STATE::END;
			return;

		case ANIMATION_STATE::END:
			g_State = ANIMATION_STATE::START;
			return;
		}
		counter = FPS;
	}
}
void Player::CheckCollided() {
	if (game->CheckCollision(x + 2, y + 2, width - 2, height - 2)) {
		p_State = PLAYER_STATE::DEAD;
		OnDied();
	}
}

void Player::SetDefaultPosition() {
	this->SetX(40);
	this->SetY(48);
	s_CanMove = 0;
	frameIdx = 0;
	g_Dir = MOVING_DIRECTION::INVALID;
	g_State = ANIMATION_STATE::START;
}

void Player::OnDied() {
	sound.CloseSound();
}
void Player::OnMoved() {
	sound.PlayBounceSound();
}

bool Player::SetY(const int& _y) {
	if (_y < GAME_SCREEN_LIMIT::TOP || _y > GAME_SCREEN_LIMIT::BOT)
		return 0;

	this->y = _y;
	return 1;
}
bool Player::SetX(const int& _x) {
	if (_x < GAME_SCREEN_LIMIT::LEFT || _x > GAME_SCREEN_LIMIT::RIGHT)
		return 0;

	this->x = _x;
	return 1;
}
void Player::ResetPosition() {
	this->SetX(40);
	this->SetY(88);
}
void Player::Move(int xDir, int yDir) {
	this->SetX(x + xDir);
	this->SetY(y + yDir);
}