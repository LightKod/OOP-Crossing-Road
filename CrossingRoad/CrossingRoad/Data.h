#pragma once
#ifndef _DATA_H_
#define _DATA_H_
#include <iostream>
#include <fstream>
#include <cwchar>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <sstream>

using namespace std;

class Data {
public:
	Data();
	Data(const wstring& name, const wstring& score);
	Data(const wstring& name, const wstring& lv,
		const wstring& score, const wstring& cIdx);

	void LoadData(const wstring&);
	void SaveData(const wstring&);
	void SaveHighscore(const wstring&);

	void SetLaneData(int index, wstring data);
	static wstring FormatDataPath(const wstring&);

protected:
	bool SetName   (const wstring& name);
	bool SetLevel  (const wstring& lv);
	bool SetScore  (const wstring& score);
	bool SetCharIdx(const wstring& cIdx);

	wstring m_Name;
	wstring m_Level;
	wstring m_Score;
	wstring m_CharIdx;


	wstring m_Date;
	wstring laneData[12];

public:
	friend class StateLoad;
	friend class StatePlay;
	friend class StateLB;

};

#endif // !_DATA_H_
