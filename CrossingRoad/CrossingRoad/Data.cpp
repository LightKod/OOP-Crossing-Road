#include "Data.h"

wstring Data::FormatDataPath(const wstring& path) const {
	return L"data/" + path + L".txt";
}
void	Data::LoadData(const wstring& path) {
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
	}
}

Data::Data() : m_Name(L""), m_Level(L""), 
				m_Date(L""), m_Score(L"")
{

}
