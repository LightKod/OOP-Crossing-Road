﻿#pragma once
#ifndef _CROSSING_GAME_H_
#define _CROSSING_GAME_H_
#include <iostream>
#include "GameEngine.h"
#include <cwchar>
#include <cstdlib>
#include <string>
#include <conio.h>

using namespace std;

#define VK_A		0x41
#define VK_D		0x44
#define VK_L		0x4C
#define VK_N		0x4E
#define VK_S		0x53
#define VK_T		0x54
#define VK_W		0x57
#define VK_Y		0x59
#define VK_E		0x45
#define VK_ENTER	0x0D

//KHONG DUOC INCLUDE MAY CAI LIEN QUAN TOI OBJECT O DAY, QUA BEN .CPP INCLUDE
class CrossingRoadGame : public GameEngine {

public:
	static Sound sCreditSound;
	class State {
	protected:
		CrossingRoadGame* game = nullptr;

	public:
		State(CrossingRoadGame* game) { this->game = game; }
		State() = default;
		//virtual ~State() { if (this->game) delete this->game; this->game = nullptr; }
		virtual bool Update(float fElapsedTime) { return true; }
		virtual bool OnStateEnter() { return true; }
		virtual bool OnStateExit() { return true; }

		// offsetX được cập nhật liên tục 
		// để xuất các chữ không đè lên nhau
		virtual void char2Pixel(const wchar_t& ch, const int& x,
			const int& y, const int& fg, const int& bg, int& offsetX);

		virtual void string2Pixel(const wstring& wStr, const int& x,
			const int& y, const int& fg, const int& bg);

	};

	void SetState(State* state) {
		if (this->state != nullptr) {
			if (this->state != state)
				delete this->state;
		}
		this->state = state;
		this->state->OnStateEnter();
	}

public:
	class Object {
	protected:
		int x, y;
		int width, height;
		CrossingRoadGame* game = nullptr;

	public:
		//Contructors de Object tuong tac duoc void Game
		Object(CrossingRoadGame* game) : Object(game, 0, 0, 0, 0) {}
		Object(CrossingRoadGame* game, int x, int y, int width, int height)
		{
			this->game = game; this->x = x; this->y = y; this->width = width; this->height = height;
		}
		Object(CrossingRoadGame* game, int x, int y) : Object(game, x, y, 0, 0) {}
		//Getters
		int GetX() { return x; };
		int GetY() { return y; };
		int GetWidth() { return width; };
		int GetHeight() { return height; };

		//Set vi tri
		void SetPosition(int x, int y) { this->x = x; this->y = y; };

		//Hai ham` ve voi Set Collision
		//Minh` se edit chu yeu 3 ham nay de ve ra Object (vi du trong class Tile)
		//Dung de update moi frame
		virtual void Update(float fElapsedTime) {};
		//Set cai ma tran collision
		virtual void SetCollisionMatrix() {};
		//Ve ra man hinh tuy` vi tri x, y
		virtual void Draw() {};

	};

public:
	CrossingRoadGame() {
		m_sAppName = L"CrossingRoad";
	}
	int GetGameWidth() { return gameScreenWidth; };
	int GetGameHeight() { return gameScreenHeight; };
	State* state = nullptr;

protected:
	virtual bool OnUserCreate();
	virtual bool OnUserUpdate(float fElapsedTime);

private:
	int gameScreenWidth = 112;
	int gameScreenHeight = 96;

public:
	void ConsOutput() {
		WriteConsoleOutput(m_hConsole, m_bufScreen, { (short)m_nScreenWidth, (short)m_nScreenHeight }, { 0,0 }, &m_rectWindow);
	}
	void ClearSprite(const int& x, const int& y, const int& w, const int& h) {
		Fill(x, y, x + w - 1, y + h - 1, L' ', COLOUR::BG_WHITE);
		ConsOutput();
	}

	static int s_CharIdx;

};

#endif // !_CROSSING_GAME_H_
