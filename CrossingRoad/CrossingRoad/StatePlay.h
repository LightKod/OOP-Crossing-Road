#pragma once
#include "CrossingRoadGame.h"
#include "Road.h"
#include "River.h"
#include "Frog.h"
#include "Dog.h"
#include "RestLane.h"
#include "Data.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "StateDead.h"
#include "TrafficLane.h"

using namespace std;

class StatePlay : public CrossingRoadGame::State 
{
protected:
	float deltaTime = 0;
	char laneSeed[10] = { 'R','G', 'G', 'G', 'G', 'G', 'T','T' ,'W' ,'W' };

	vector<Lane*> lanes;
	Player* pPlayer = nullptr;

	int score = 0;
	int charIdx = CrossingRoadGame::s_CharIdx;

	wchar_t prevLane = L'0';


private:
	int optionIndex = 0;

	int saveIndex = 0;

	bool pause = false;
	bool endState = false;

	wstring saveName = L"";
	int level = 1;

	wstring date;
	wstring* dataNames = nullptr;
	bool isLoaded = false;

	float ToTalTimeConsume = 0.f;

public:
	StatePlay(CrossingRoadGame* game) : State(game) {
	}
	StatePlay(CrossingRoadGame* game, const wstring& fileName) : StatePlay(game) {
		LoadLevel(fileName);
		isLoaded = true;
	}
	StatePlay(CrossingRoadGame* game, const wstring& savedName,
		const wstring& lv, const wstring& score, const wstring& cIdx) : State(game) {
		this->saveName = savedName;
		this->level = stoi(lv);
		this->score = stoi(score);
		this->charIdx = stoi(cIdx);
	}
	
	virtual bool Update(float fElapsedTime);
	virtual bool OnStateEnter();
	virtual bool OnStateExit();


protected:
	virtual void UpdateScorePerLV();
	virtual void UpdateCollisionMatrix();
	virtual void UpdateGameScreen();
	virtual void UpdateGameState(float fElapsedTime);

	virtual void GenerateNewLevel();
	virtual void DrawGameScreen();
	virtual void DrawSideBar();

	Lane* GetRandomLane(int index);
	void ClearCurrentLevel();


private:
	void DrawSaveSystem();

	void DrawSaveBox(const int& x = 32, const int& y = 32);
	void DrawChooseSaveSlot(const int& x = 16, const int& y = 16);
	void DrawContinue(const int& x = 48, const int& y = 32);

	void HandleInput();

	void HandleSaveInput();
	void HandleEnterName();
	void HandleChooseSlot();
	void HandleContinue();

	void NextLevel();
	void LoadLevel(const wstring& fileName);
	void ExportGameData(const wstring& path);
	

	void DrawBoxAnimationOpen(const int& x, const int& y, const int& width, const int& height);
	void DrawBoxAnimationClose(const int& x, const int& y, const int& width, const int& height);


	void LevelUp(const int& x = -75, const int& y = 36);
	void LVUP_Border(const int& x, const int& y);
	void LVUP_TopColor(const int& x, const int& y, const short& fg, const short& bg);
	void LVUP_BotColor(const int& x, const int& y, const short& fg, const short& bg);
	void LVUP_MidLine(const int& x, const int& y);

};

