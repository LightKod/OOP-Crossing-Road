#include "Frog.h"

bool Frog::s_CanMove = 1;

Frog::Frog(CrossingRoadGame* game)
	: Player(game,
		game->ScreenWidth() / 8 * 2,
		game->ScreenHeight() - s_CellSize,
		s_CellSize, s_CellSize)
{
	sprAvatar = new olcSprite(L"spr/frog.spr");

	// Set up default state
	s_CanMove = 1;
	g_Dir = MOVING_DIRECTION::INVALID;
	g_State = ANIMATION_STATE::START;
	frogsound.OpenFrogSound();
}

void Frog::Update(float fElapsedTime) {
	if (game->m_keys[VK_W].bReleased) {
		if(this->MoveUp())
			frogsound.PlayFrogSound();
	}
	if (game->m_keys[VK_S].bReleased) {
		if(this->MoveDown())
			frogsound.PlayFrogSound();
	}
	if (game->m_keys[VK_A].bReleased) {
		if(this->MoveLeft())
			frogsound.PlayFrogSound();
	}
	if (game->m_keys[VK_D].bReleased) {
		if(this->MoveRight())
			frogsound.PlayFrogSound();
	}
	
	CheckCollided();
}

void Frog::Draw() {
	switch (g_State) {
	case ANIMATION_STATE::START:
		Standing();
		s_CanMove = 1;
		return;

	case ANIMATION_STATE::READY:
		ReadyJumpAndLanding();
		g_State = ANIMATION_STATE::JUMP;
		break;

	case ANIMATION_STATE::JUMP:
		JumpHandle();
		break;

	case ANIMATION_STATE::LANDING:
		ReadyJumpAndLanding();
		g_State = ANIMATION_STATE::END;
		break;

	case ANIMATION_STATE::END:
		Standing();
		g_State = ANIMATION_STATE::START;
		break;

	default:
		Standing();
		return;
	}

	// pause thread
	this_thread::sleep_for(std::chrono::milliseconds(25));
}

void Frog::CheckCollided() {
	if (game->CheckCollision(x, y, width, height)) {
		p_State = PLAYER_STATE::DEAD;
		frogsound.CloseSound();
	}
}

void Frog::JumpHandle() {
	static const int sFrameOfJumpState = 4;
	static int frameIdx = 0;

	switch (g_Dir) {
	case MOVING_DIRECTION::MOVING_UP:
		this->Move(0, -s_CellSize / 8);
		Jumping();
		this->Move(0, -s_CellSize / 8);
		break;

	case MOVING_DIRECTION::MOVING_DOWN:
		this->Move(0, s_CellSize / 8);
		Jumping();
		this->Move(0, s_CellSize / 8);
		break;

	case MOVING_DIRECTION::MOVING_LEFT:
		this->Move(-s_CellSize / 8, 0);
		Jumping();
		this->Move(-s_CellSize / 8, 0);
		break;

	case MOVING_DIRECTION::MONIG_RIGHT:
		this->Move(s_CellSize / 8, 0);
		Jumping();
		this->Move(s_CellSize / 8, 0);
		break;

	default:
		break;
	}

	if (++frameIdx >= sFrameOfJumpState) {
		g_State = ANIMATION_STATE::LANDING;
		frameIdx = 0;
	}
}


// Handle moving player
bool Frog::MoveUp(const int& dY) {
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
bool Frog::MoveDown(const int& dY) {
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
bool Frog::MoveLeft(const int& dX) {
	if (!s_CanMove)
		return 0;

	if ((this->GetX() - dX) >= GAME_SCREEN_LIMIT::LEFT) {
		g_Dir = MOVING_DIRECTION::MOVING_LEFT;
		g_State = ANIMATION_STATE::READY;
		s_CanMove = false;
		return 1;
	}
	return 0;
}
bool Frog::MoveRight(const int& dX) {
	if (!s_CanMove)
		return 0;

	if ((this->GetX() + dX) < GAME_SCREEN_LIMIT::RIGHT) {
		g_Dir = MOVING_DIRECTION::MONIG_RIGHT;
		g_State = ANIMATION_STATE::READY;
		s_CanMove = false;
		return 1;
	}
	return 0;
}


void Frog::Standing() {
	game->DrawSprite(x, y, sprAvatar);
}
void Frog::ReadyJumpAndLanding() {
	// row 0
	int row = 0;

	// row 1
	row++;

	// row 2
	row++;
	game->DrawLine(x + 1, y + row, x + 2, y + row, 9608, FG_DARK_GREEN);
	game->DrawLine(x + 5, y + row, x + 6, y + row, 9608, FG_DARK_GREEN);

	// row 3
	row++;
	game->Draw(x, y + row, 9608, FG_DARK_GREEN);
	game->Draw(x + 1, y + row, 9608, FG_WHITE);
	game->Draw(x + 2, y + row, 9608, FG_BLACK);
	game->DrawLine(x + 3, y + row, x + 4, y + row, 9608, FG_DARK_GREEN);
	game->Draw(x + 5, y + row, 9608, FG_BLACK);
	game->Draw(x + 6, y + row, 9608, FG_WHITE);
	game->Draw(x + 7, y + row, 9608, FG_DARK_GREEN);

	// row 4
	row++;
	game->Draw(x, y + row, 9608, FG_DARK_GREEN);
	game->DrawLine(x + 1, y + row, x + 2, y + row, 9608, FG_WHITE);
	game->DrawLine(x + 3, y + row, x + 4, y + row, 9608, FG_DARK_GREEN);
	game->DrawLine(x + 5, y + row, x + 6, y + row, 9608, FG_WHITE);
	game->Draw(x + 7, y + row, 9608, FG_DARK_GREEN);

	// row 5
	row++;
	game->DrawLine(x + 1, y + row, x + 6, y + row, 9608, FG_DARK_GREEN);

	// row 6
	row++;
	game->Draw(x + 1, y + row, 9608, FG_DARK_GREEN);
	game->DrawLine(x + 2, y + row, x + 5, y + row, 9608, FG_GREEN);
	game->Draw(x + 6, y + row, 9608, FG_DARK_GREEN);

	// row 7
	row++;
	game->DrawLine(x, y + row, x + 2, y + row, 9608, FG_DARK_GREEN);
	game->DrawLine(x + 3, y + row, x + 4, y + row, 9608, FG_GREEN);
	game->DrawLine(x + 5, y + row, x + 7, y + row, 9608, FG_DARK_GREEN);
}
void Frog::Jumping() {
	// row 0
	int row = 0;
	game->DrawLine(x + 1, y + row, x + 2, y + row, 9608, FG_DARK_GREEN);
	game->DrawLine(x + 5, y + row, x + 6, y + row, 9608, FG_DARK_GREEN);

	// row 1
	row++;
	game->Draw(x, y + row, 9608, FG_DARK_GREEN);
	game->DrawLine(x + 1, y + row, x + 2, y + row, 9608, FG_WHITE);
	game->DrawLine(x + 3, y + row, x + 4, y + row, 9608, FG_DARK_GREEN);
	game->DrawLine(x + 5, y + row, x + 6, y + row, 9608, FG_WHITE);
	game->Draw(x + 7, y + row, 9608, FG_DARK_GREEN);

	// row 2
	row++;
	game->Draw(x, y + row, 9608, FG_DARK_GREEN);
	game->Draw(x + 1, y + row, 9608, FG_WHITE);
	game->Draw(x + 2, y + row, 9608, FG_BLACK);
	game->DrawLine(x + 3, y + row, x + 4, y + row, 9608, FG_DARK_GREEN);
	game->Draw(x + 5, y + row, 9608, FG_BLACK);
	game->Draw(x + 6, y + row, 9608, FG_WHITE);
	game->Draw(x + 7, y + row, 9608, FG_DARK_GREEN);

	// row 3
	row++;
	game->DrawLine(x + 1, y + row, x + 6, y + row, 9608, FG_DARK_GREEN);

	// row 4
	row++;
	game->DrawLine(x + 1, y + row, x + 2, y + row, 9608, FG_DARK_GREEN);
	game->DrawLine(x + 3, y + row, x + 4, y + row, 9608, FG_RED);
	game->DrawLine(x + 5, y + row, x + 6, y + row, 9608, FG_DARK_GREEN);

	// row 5
	row++;
	game->Draw(x + 1, y + row, 9608, FG_DARK_GREEN);
	game->DrawLine(x + 2, y + row, x + 5, y + row, 9608, FG_GREEN);
	game->Draw(x + 6, y + row, 9608, FG_DARK_GREEN);

	// row 6
	row++;
	game->Draw(x + 1, y + row, 9608, FG_DARK_GREEN);
	game->Draw(x + 6, y + row, 9608, FG_DARK_GREEN);

	// row 7
	row++;
	game->Draw(x + 1, y + row, 9608, FG_DARK_GREEN);
	game->Draw(x + 6, y + row, 9608, FG_DARK_GREEN);
}


Frog::~Frog() {
	if (sprAvatar) {
		delete sprAvatar;
		sprAvatar = nullptr;
	}
}