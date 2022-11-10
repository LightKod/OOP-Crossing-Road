#pragma once
#ifndef _DATA_H_
#define _DATA_H_
#include <iostream>
#include <fstream>
#include <cwchar>
#include <cstdlib>
#include <string>
#include <algorithm>

using namespace std;

class Data {
public:
	Data();

	void LoadData(const wstring&);

protected:
	wstring FormatDataPath(const wstring&) const;

	wstring m_Name;
	wstring m_Level;
	wstring m_Date;
	wstring m_Score;

public:
	friend class StateLoad;
	friend class StateLB;
};


#endif // !_DATA_H_


