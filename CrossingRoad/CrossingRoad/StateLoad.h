#pragma once
#ifndef _STATE_LOAD_H_
#define _STATE_LOAD_H_
#include "CrossingRoadGame.h"
#include "Data.h"

class StateLoad : public CrossingRoadGame::State
{
public:
	virtual bool Update(float fElapsedTime);
	virtual bool OnStateEnter();
	virtual bool OnStateExit();

	StateLoad(CrossingRoadGame* game) : State(game) {};

	void LoadingThread();

protected:
	// Hiệu ứng load data
	void LoadingAnimation();

	// Xử lý hiệu ứng cho title
	void DrawTitle();

	// Xử lý đồ họa arrow & checkbox
	void UpdateArrowCoord();
	void SetArrowCoord(const COORD&);
	void MoveArrow(const int&);
	void DrawArrow();

	void UpdateCheckbox();
	void UpdateCheckbox1();
	void UpdateCheckbox2();
	void UpdateCheckbox3();
	void UpdateCheckbox4();

	void DrawCheckbox(const COORD&,
		const short& fg, const short& bg);

	// Xử lý phần thân của bản đồ loadgame
	void DrawLoadingScreen();

	void LS_FillBackground();
	void LS_DrawBorder();
	// Trang trí
	void LS_DecorateScreen();
	void DrawMagnifyingGlass();
	void DrawMarkXTreasure();

	void GetDataRecord();
	void ModifyDataRecord();
	void ShowDataRecord();

	void UpdateDataLine1();
	void UpdateDataLine2();
	void UpdateDataLine3();
	void UpdateDataLine4();

private:
	COORD m_ArrowCoord{ 0,0 };
	int m_OptionIdx = 0;
	vector<Data> m_Datas;

	static const int S_MAX_DATA_LINE;

	static const int m_s_OFFSET_X;
	static const int m_s_X0;
	static const int m_s_X1;
	static const int m_s_Y0;
	static const int m_s_Y1;

	static const COORD m_s_LINE_1;
	static const COORD m_s_LINE_2;
	static const COORD m_s_LINE_3;
	static const COORD m_s_LINE_4;

};

#endif // !_STATE_LOAD_H_
