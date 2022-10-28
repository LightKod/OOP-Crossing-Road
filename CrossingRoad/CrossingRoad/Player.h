#pragma once
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "Object.h"


static int cellSize = 8;

class Player : public Object
{
public:
	Player() : Object(56, 88, 8, 8)
	{
		sprAvatar = new olcSprite(L"spr/frog.spr");
	}
	~Player()
	{
		delete sprAvatar;
		sprAvatar = nullptr;
	}

	virtual void Draw(CrossingRoadGame& game) const
	{
		game.DrawSprite(x, y, sprAvatar);
	}
	virtual void Animation(CrossingRoadGame& game) const
	{
		// clear old sprite
		
	}
	virtual void Prep(CrossingRoadGame& game) const
	{
		// game.Fill(x, y, x + 16, y + 16, L' ', FG_BLACK);
		int row = 0;
		// row 0

		// row 1
		row++;
		game.DrawLine(x + 1, y + row, x + 2, y + row, 9608, FG_DARK_GREEN);
		game.DrawLine(x + 5, y + row, x + 6, y + row, 9608, FG_DARK_GREEN);

		// row 2
		row++;
		game.Draw(x, y + row, 9608, FG_DARK_GREEN);
		game.DrawLine(x + 1, y + row, x + 2, y + row, 9608, FG_WHITE);
		game.DrawLine(x + 3, y + row, x + 4, y + row, 9608, FG_DARK_GREEN);
		game.DrawLine(x + 1, y + row, x + 2, y + row, 9608, FG_WHITE);
		game.Draw(x + 7, y + row, 9608, FG_DARK_GREEN);

		// row 4
		// 
		// row 5
		// row 6
		// row 7
		// row 8
		game.ConsOutput();
	}
	// Handle moving player
	virtual void MoveUp(CrossingRoadGame& game, const int& dY = cellSize)
	{
		//game.ClearSprite(x, y, width, height);
		Prep(game);
		if ((this->GetY() - dY) >= 0)
			this->Move(0, -dY);
	}
	virtual void MoveDown(CrossingRoadGame& game, const int& dY = cellSize)
	{
		if ((this->GetY() + dY) < game.ScreenHeight())
			this->Move(0, dY);
	}
	virtual void MoveLeft(CrossingRoadGame& game, const int& dX = cellSize)
	{
		if ((this->GetX() - dX) >= 0)
			this->Move(-dX, 0);
	}
	virtual void MoveRight(CrossingRoadGame& game, const int& dX = cellSize)
	{
		if ((this->GetX() + dX) < game.ScreenWidth())
			this->Move(dX, 0);
	}

	/*virtual void PlayerHanle(CrossingRoadGame& game) const
	{
	}*/

protected:
	virtual bool SetX(const int& x)
	{
		this->x = x;
		return 1;
	}
	virtual bool SetY(const int& y)
	{
		this->y = y;
		return 1;
	}
private:
	olcSprite* sprAvatar = nullptr;

};

#endif // !_PLAYER_H_


