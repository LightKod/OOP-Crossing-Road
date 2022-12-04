#include "Data.h"

wstring Data::FormatDataPath(const wstring& path) {
	return L"data/" + path + L".txt";
}
void Data::LoadData(const wstring& path) {
	wifstream wIfs(FormatDataPath(path));
	if (wIfs.is_open()) {
		
		// Load data process
		// Name
		getline(wIfs, m_Name);
		
		// Level
		getline(wIfs, m_Level);

		// Date
		getline(wIfs, m_Date);

		// Score
		getline(wIfs, m_Score);

		wIfs.close();
		/*wstring temp;
		for (int i = 0; i < 12; i++) {
			getline(wIfs, temp, L'|');
			laneCodes[i] = temp[0];
		}*/
	}
}

void Data::SaveData(const wstring& path) {
	//file << m_Name << endl;
	//file << m_Level << endl;
	//file << m_Date << endl;
	//file << m_Score << endl;

	//for (int i = 0; i < 12; i++) {
	//	file << laneData[i];
	//}
	//cout << endl;

	wofstream file(FormatDataPath(path), ios_base::app);
	if (file.is_open()) {
		// format: TEN,LEVEL,SCORE,CHAR_IDX
		file << m_Name << L",";
		file << m_Level << L",";
		file << m_Score << L",";
		file << m_CharIdx << endl;

		file.close();
	}
}
void Data::SaveHighscore(const wstring& path) {
	wofstream file(FormatDataPath(path), ios_base::app);
	if (file.is_open()) {
		// format: TEN,SCORE
		file << m_Name << L",";
		file << m_Score << endl;

		file.close();
	}
}

bool Data::SetName(const wstring& name) {
	this->m_Name = name;
	return 1;
}
bool Data::SetLevel(const wstring& lv) {
	if (lv < L"1" || lv > L"5") {
		return 0;
	}

	this->m_Level = lv;
	return 1;
}
bool Data::SetScore(const wstring& score) {
	if (score < L"0") {
		return 0;
	}
	this->m_Score = score;
	return 1;
}
bool Data::SetCharIdx(const wstring& cIdx) {
	if (cIdx == L"0" || cIdx == L"1") {
		this->m_CharIdx = cIdx;
		return 1;
	}
	return 0;
}

Data::Data() : m_Name(L""), m_Level(L""), 
				m_Date(L""), m_Score(L""), m_CharIdx(L"")
{

}
Data::Data(const wstring& name, const wstring& score) : Data() {
	this->SetName(name);
	this->SetScore(score);
}
Data::Data(const wstring& name, const wstring& lv,
	const wstring& score, const wstring& cIdx) : Data() {
	this->SetName(name);
	this->SetLevel(lv);
	this->SetScore(score);
	this->SetCharIdx(cIdx);
}
void Data::SetLaneData(int index, wstring data) {
	laneData[index] = data;
}
