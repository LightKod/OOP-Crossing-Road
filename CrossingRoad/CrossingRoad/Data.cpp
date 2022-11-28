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

void Data::SaveData(const wstring path) {
	wofstream file(FormatDataPath(path));
	file << m_Name << endl;
	file << m_Level << endl;
	file << m_Date << endl;
	file << m_Score << endl;

	for (int i = 0; i < 12; i++) {
		file << laneData[i];
	}
	cout << endl;
}

Data::Data() : m_Name(L""), m_Level(L""), 
				m_Date(L""), m_Score(L"")
{

}

void Data::SetLaneData(int index, wstring data) {
	laneData[index] = data;
}
