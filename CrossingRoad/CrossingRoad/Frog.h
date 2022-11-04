#pragma once
#include "Player.h"

#define INIT_TIME float(24.f)
#define LIMIT_TIME float(28.f)

static const int s_CellSize = 8;
static bool s_CanMove = 1;
static float s_Time = INIT_TIME;

class Frog : public Player
{
public:
	Frog(CrossingRoadGame* game)
		: Player(game,
			game->ScreenWidth() / 8 * 2,
			game->ScreenHeight() - s_CellSize,
			s_CellSize, s_CellSize)
	{
		sprAvatar = new olcSprite(L"spr/frog.spr");

		// Set up default state
		s_CanMove = 1;
		s_Time = INIT_TIME;
		g_Dir = MOVING_DIRECTION::INVALID;
		g_State = ANIMATION_STATE::START;
	}
	~Frog()
	{
		if (sprAvatar)
		{
			delete sprAvatar;
			sprAvatar = nullptr;
		}
	}
	virtual void Update(float fElapsedTime)
	{

		if (game->m_keys[VK_W].bReleased) this->MoveUp();
		if (game->m_keys[VK_S].bReleased) this->MoveDown();
		if (game->m_keys[VK_A].bReleased) this->MoveLeft();
		if (game->m_keys[VK_D].bReleased) this->MoveRight();

		s_Time += int(fElapsedTime) * 1000;
		if (s_Time >= LIMIT_TIME)
		{
			s_Time = INIT_TIME;
		}
		CheckCollided();
	}

	virtual void Draw()
	{
		switch (g_State)
		{
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
		//this_thread::sleep_for(std::chrono::milliseconds(int(s_Time)));
		this_thread::sleep_for(std::chrono::milliseconds(int(24)));
	}
protected:
	void CheckCollided() {
		if (game->CheckCollision(x, y, width, height)) {
			this_thread::sleep_for(std::chrono::milliseconds(int(1000)));
		}
	}

	virtual void JumpHandle()
	{
		static const int sFrameOfJumpState = 4;
		static int frameIdx = 0;
		s_Time += 0.3f;

		switch (g_Dir)
		{
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

		if (++frameIdx >= sFrameOfJumpState)
		{
			g_State = ANIMATION_STATE::LANDING;
			frameIdx = 0;
		}
	}

	virtual void Standing()
	{
		game->DrawSprite(x, y, sprAvatar);
	}
	virtual void ReadyJumpAndLanding()
	{
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
	virtual void Jumping()
	{
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

	// Handle moving player
	virtual bool MoveUp(const int& dY = s_CellSize)
	{
		if (!s_CanMove)
			return 0;

		if ((this->GetY() - dY) >= 0)
		{
			//this->Move(0, -dY);
			g_Dir = MOVING_DIRECTION::MOVING_UP;
			g_State = ANIMATION_STATE::READY;
			s_CanMove = false;
			return 1;
		}
		return 0;
	}
	virtual bool MoveDown(const int& dY = s_CellSize)
	{
		if (!s_CanMove)
			return 0;

		if ((this->GetY() + dY) < game->ScreenHeight())
		{
			//this->Move(0, dY);
			g_Dir = MOVING_DIRECTION::MOVING_DOWN;
			g_State = ANIMATION_STATE::READY;
			s_CanMove = false;
			return 1;
		}
		return 0;
	}
	virtual bool MoveLeft(const int& dX = s_CellSize)
	{
		if (!s_CanMove)
			return 0;

		if ((this->GetX() - dX) >= 0)
		{
			//this->Move(-dX, 0);
			g_Dir = MOVING_DIRECTION::MOVING_LEFT;
			g_State = ANIMATION_STATE::READY;
			s_CanMove = false;
			return 1;
		}
		return 0;
	}
	virtual bool MoveRight(const int& dX = s_CellSize)
	{
		if (!s_CanMove)
			return 0;

		if ((this->GetX() + dX) < game->ScreenWidth())
		{
			//this->Move(dX, 0);
			g_Dir = MOVING_DIRECTION::MONIG_RIGHT;
			g_State = ANIMATION_STATE::READY;
			s_CanMove = false;
			return 1;
		}
		return 0;
	}

private:
	olcSprite* sprAvatar = nullptr;
	MOVING_DIRECTION g_Dir = MOVING_DIRECTION::INVALID;
	ANIMATION_STATE g_State = ANIMATION_STATE::START;
};

