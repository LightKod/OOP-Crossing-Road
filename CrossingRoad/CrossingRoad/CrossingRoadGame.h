#pragma once
#include <iostream>
#include "GameEngine.h"

//KHONG DUOC INCLUDE MAY CAI LIEN QUAN TOI OBJECT O DAY, QUA BEN .CPP INCLUDE
class CrossingRoadGame : public GameEngine {

public:
	class State
	{
	protected:
		CrossingRoadGame* game;
	public:
		State(CrossingRoadGame* game) { this->game = game; }
		virtual bool Update(float fElapsedTime) { return true; }
		virtual bool OnStateEnter() { return true; }
		virtual bool OnStateExit() { return true; }
	};

	void SetState(State* state) {
		if (this->state != nullptr) this->state->OnStateExit();
		this->state = state;
		this->state->OnStateEnter();
	}
public:
	class Object
	{
	protected:
		int x, y;
		int width, height;
		CrossingRoadGame* game;

	public:
		//Contructors de Object tuong tac duoc void Game
		Object(CrossingRoadGame* game) { this->game = game; };
		Object(CrossingRoadGame* game, int x, int y, int width, int height) { this->game = game; this->x = x; this->y = y; this->width = width; this->height = height; };
		Object(CrossingRoadGame* game, int x, int y) { this->game = game; this->x = x; this->y = y; };

		//Getters
		int GetX() { return x; };
		int GetY() { return y; };
		int GetWidth() { return width; };
		int GetHeight() { return height; };

		//Set vi tri
		bool SetPosition(int x, int y) { this->x = x; this->y = y; };


		//Hai ham` ve voi Set Collision
		//Minh` se edit chu yeu 3 ham nay de ve ra Object (vi du trong class Tile)
		//Dung de update moi frame
		virtual void Update(float fElapsedTime) {};
		//Set cai ma tran collision
		virtual void SetCollisionMatrix() {};
		//Ve ra man hinh tuy` vi tri x, y
		virtual void Draw() {};

		//Check coi Object co dang de` len CollisionMatrix ko
		bool CheckCollided() { return false; };
	};
public:
	CrossingRoadGame() {
		m_sAppName = L"CrossingRoad";
	}
	int GetGameWidth() { return gameScreenWidth; };
	int GetGameHeight() { return gameScreenHeight; };
	State* state;

protected:
	virtual bool OnUserCreate();
	virtual bool OnUserUpdate(float fElapsedTime);

private:
	int gameScreenWidth = 112;
	int gameScreenHeight = 96;
private:
	public:
		void ConsOutput()
		{
			WriteConsoleOutput(m_hConsole, m_bufScreen, { (short)m_nScreenWidth, (short)m_nScreenHeight }, { 0,0 }, &m_rectWindow);
		}
		void ClearSprite(const int& x, const int& y, const int& w, const int& h)
		{
			Fill(x, y, x + w -1, y + h-1, L' ', COLOUR::BG_WHITE);
			ConsOutput();
		}
};


