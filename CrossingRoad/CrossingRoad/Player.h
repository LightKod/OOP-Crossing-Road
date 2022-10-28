#pragma once
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "Object.h"

#define VK_A 0x41
#define VK_D 0x44
#define VK_S 0x53
#define VK_W 0x57

#define INIT_TIME float(24.f)
#define LIMIT_TIME float(28.f)

static const int s_CellSize = 8;
static bool s_CanMove = 1;
static float s_Time = INIT_TIME;

class Player : public Object
{
public:
	Player(CrossingRoadGame& game) 
		: Object(game.ScreenWidth() / 8 * 2,
				 game.ScreenHeight() - s_CellSize,
				 s_CellSize, s_CellSize)
	{
		sprAvatar = new olcSprite(L"spr/frog.spr");
		
		// Set up default state
		s_CanMove = 1;
		s_Time = INIT_TIME;
		g_Dir = MOVING_DIRECTION::INVALID;
		g_State = ANIMATION_STATE::START;
	}
	~Player()
	{
		delete sprAvatar;
		sprAvatar = nullptr;
	}

	virtual void Update(CrossingRoadGame& game, float fElapsedTime)
	{
		if (game.m_keys[VK_W].bReleased) this->MoveUp(game);
		if (game.m_keys[VK_S].bReleased) this->MoveDown(game);
		if (game.m_keys[VK_A].bReleased) this->MoveLeft(game);
		if (game.m_keys[VK_D].bReleased) this->MoveRight(game);
		
		s_Time += int(fElapsedTime) * 1000;
		if (s_Time >= LIMIT_TIME)
		{
			s_Time = INIT_TIME;
		}
	}

	virtual void Draw(CrossingRoadGame& game)
	{
		switch (g_State)
		{
		case ANIMATION_STATE::START:
			Standing(game);
			s_CanMove = 1;
			break;

		case ANIMATION_STATE::READY:
			ReadyJumpAndLanding(game);
			g_State = ANIMATION_STATE::JUMP;
			break;
		
		case ANIMATION_STATE::JUMP:
			JumpHandle(game);
			break;

		case ANIMATION_STATE::LANDING:
			ReadyJumpAndLanding(game);
			g_State = ANIMATION_STATE::END;
			break;

		case ANIMATION_STATE::END:
			Standing(game);
			g_State = ANIMATION_STATE::START;
			break;

		default:
			Standing(game);
			break;
		}

		game.ConsOutput();

		// pause thread
		//this_thread::sleep_for(std::chrono::milliseconds(int(s_Time)));
		this_thread::sleep_for(std::chrono::milliseconds(int(30)));
	}

protected:
	virtual void JumpHandle(CrossingRoadGame& game)
	{
		static const int sFrameOfJumpState = 4;
		static int frameIdx = 0;
		s_Time += 0.3f;

		switch (g_Dir)
		{
		case MOVING_DIRECTION::MOVING_UP:
			this->Move(0, -s_CellSize / 8);
			Jumping(game);
			this->Move(0, -s_CellSize / 8);
			break;

		case MOVING_DIRECTION::MOVING_DOWN:
			this->Move(0, s_CellSize / 8);
			Jumping(game);
			this->Move(0, s_CellSize / 8);
			break;

		case MOVING_DIRECTION::MOVING_LEFT:
			this->Move(-s_CellSize / 8, 0);
			Jumping(game);
			this->Move(-s_CellSize / 8, 0);
			break;

		case MOVING_DIRECTION::MONIG_RIGHT:
			this->Move(s_CellSize / 8, 0);
			Jumping(game);
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

	virtual void Standing(CrossingRoadGame& game) 
	{
		game.DrawSprite(x, y, sprAvatar);
	}
	virtual void ReadyJumpAndLanding(CrossingRoadGame& game) 
	{
		// row 0
		int row = 0;

		// row 1
		row++;

		// row 2
		row++;
		game.DrawLine(x + 1, y + row, x + 2, y + row, 9608, FG_DARK_GREEN);
		game.DrawLine(x + 5, y + row, x + 6, y + row, 9608, FG_DARK_GREEN);

		// row 3
		row++;
		game.Draw(x, y + row, 9608, FG_DARK_GREEN);
		game.Draw(x + 1, y + row, 9608, FG_WHITE);
		game.Draw(x + 2, y + row, 9608, FG_BLACK);
		game.DrawLine(x + 3, y + row, x + 4, y + row, 9608, FG_DARK_GREEN);
		game.Draw(x + 5, y + row, 9608, FG_BLACK);
		game.Draw(x + 6, y + row, 9608, FG_WHITE);
		game.Draw(x + 7, y + row, 9608, FG_DARK_GREEN);

		// row 4
		row++;
		game.Draw(x, y + row, 9608, FG_DARK_GREEN);
		game.DrawLine(x + 1, y + row, x + 2, y + row, 9608, FG_WHITE);
		game.DrawLine(x + 3, y + row, x + 4, y + row, 9608, FG_DARK_GREEN);
		game.DrawLine(x + 5, y + row, x + 6, y + row, 9608, FG_WHITE);
		game.Draw(x + 7, y + row, 9608, FG_DARK_GREEN);

		// row 5
		row++;
		game.DrawLine(x + 1, y + row, x + 6, y + row, 9608, FG_DARK_GREEN);

		// row 6
		row++;
		game.Draw(x + 1, y + row, 9608, FG_DARK_GREEN);
		game.DrawLine(x + 2, y + row, x + 5, y + row, 9608, FG_GREEN);
		game.Draw(x + 6, y + row, 9608, FG_DARK_GREEN);

		// row 7
		row++;
		game.DrawLine(x, y + row, x + 2, y + row, 9608, FG_DARK_GREEN);
		game.DrawLine(x + 3, y + row, x + 4, y + row, 9608, FG_GREEN);
		game.DrawLine(x + 5, y + row, x + 7, y + row, 9608, FG_DARK_GREEN);
	}
	virtual void Jumping(CrossingRoadGame& game) 
	{
		// row 0
		int row = 0;
		game.DrawLine(x + 1, y + row, x + 2, y + row, 9608, FG_DARK_GREEN);
		game.DrawLine(x + 5, y + row, x + 6, y + row, 9608, FG_DARK_GREEN);

		// row 1
		row++;
		game.Draw(x, y + row, 9608, FG_DARK_GREEN);
		game.DrawLine(x + 1, y + row, x + 2, y + row, 9608, FG_WHITE);
		game.DrawLine(x + 3, y + row, x + 4, y + row, 9608, FG_DARK_GREEN);
		game.DrawLine(x + 5, y + row, x + 6, y + row, 9608, FG_WHITE);
		game.Draw(x + 7, y + row, 9608, FG_DARK_GREEN);

		// row 2
		row++;
		game.Draw(x, y + row, 9608, FG_DARK_GREEN);
		game.Draw(x + 1, y + row, 9608, FG_WHITE);
		game.Draw(x + 2, y + row, 9608, FG_BLACK);
		game.DrawLine(x + 3, y + row, x + 4, y + row, 9608, FG_DARK_GREEN);
		game.Draw(x + 5, y + row, 9608, FG_BLACK);
		game.Draw(x + 6, y + row, 9608, FG_WHITE);
		game.Draw(x + 7, y + row, 9608, FG_DARK_GREEN);

		// row 3
		row++;
		game.DrawLine(x + 1, y + row, x + 6, y + row, 9608, FG_DARK_GREEN);

		// row 4
		row++;
		game.DrawLine(x + 1, y + row, x + 2, y + row, 9608, FG_DARK_GREEN);
		game.DrawLine(x + 3, y + row, x + 4, y + row, 9608, FG_RED);
		game.DrawLine(x + 5, y + row, x + 6, y + row, 9608, FG_DARK_GREEN);

		// row 5
		row++;
		game.Draw(x + 1, y + row, 9608, FG_DARK_GREEN);
		game.DrawLine(x + 2, y + row, x + 5, y + row, 9608, FG_GREEN);
		game.Draw(x + 6, y + row, 9608, FG_DARK_GREEN);

		// row 6
		row++;
		game.Draw(x + 1, y + row, 9608, FG_DARK_GREEN);
		game.Draw(x + 6, y + row, 9608, FG_DARK_GREEN);

		// row 7
		row++;
		game.Draw(x + 1, y + row, 9608, FG_DARK_GREEN);
		game.Draw(x + 6, y + row, 9608, FG_DARK_GREEN);
	}

	// Handle moving player
	virtual bool MoveUp(CrossingRoadGame& game, const int& dY = s_CellSize)
	{
		if (!s_CanMove)
			return 0;

		if ((this->GetY() - dY) >= 0)
		{
			//this->Move(0, -dY);
			g_Dir = MOVING_DIRECTION::MOVING_UP;
			g_State = ANIMATION_STATE::READY;
			return 1;
		}
		return 0;
	}
	virtual bool MoveDown(CrossingRoadGame& game, const int& dY = s_CellSize)
	{
		if (!s_CanMove)
			return 0;

		if ((this->GetY() + dY) < game.ScreenHeight())
		{
			//this->Move(0, dY);
			g_Dir = MOVING_DIRECTION::MOVING_DOWN;
			g_State = ANIMATION_STATE::READY;
			return 1;
		}
		return 0;
	}
	virtual bool MoveLeft(CrossingRoadGame& game, const int& dX = s_CellSize)
	{
		if (!s_CanMove)
			return 0;

		if ((this->GetX() - dX) >= 0)
		{
			//this->Move(-dX, 0);
			g_Dir = MOVING_DIRECTION::MOVING_LEFT;
			g_State = ANIMATION_STATE::READY;
			return 1;
		}
		return 0;
	}
	virtual bool MoveRight(CrossingRoadGame& game, const int& dX = s_CellSize)
	{
		if (!s_CanMove)
			return 0;

		if ((this->GetX() + dX) < game.ScreenWidth())
		{
			//this->Move(dX, 0);
			g_Dir = MOVING_DIRECTION::MONIG_RIGHT;
			g_State = ANIMATION_STATE::READY;
			return 1;
		}
		return 0;
	}

private:
	enum class MOVING_DIRECTION
	{
		INVALID = 0,
		MOVING_UP,
		MOVING_DOWN,
		MOVING_LEFT,
		MONIG_RIGHT,
	};
	enum class ANIMATION_STATE
	{
		START = 0,
		READY,
		JUMP,
		LANDING,
		END,
	};

	olcSprite* sprAvatar = nullptr;
	MOVING_DIRECTION g_Dir = MOVING_DIRECTION::INVALID;
	ANIMATION_STATE g_State = ANIMATION_STATE::START;
};


#endif // !_PLAYER_H_