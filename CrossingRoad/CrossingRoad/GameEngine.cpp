#include "GameEngine.h"

GameEngine::GameEngine()
	{
		m_nScreenWidth = 80;
		m_nScreenHeight = 30;

		m_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		m_hConsoleIn = GetStdHandle(STD_INPUT_HANDLE);

		std::memset(m_keyNewState, 0, 256 * sizeof(short));
		std::memset(m_keyOldState, 0, 256 * sizeof(short));
		std::memset(m_keys, 0, 256 * sizeof(sKeyState));

		m_bEnableSound = false;

		m_sAppName = L"Default";
	}


int GameEngine::ConstructConsole(int width, int height, int fontw, int fonth)
{
	if (m_hConsole == INVALID_HANDLE_VALUE)
		return Error(L"Bad Handle");

	m_nScreenWidth = width;
	m_nScreenHeight = height;

	// Update 13/09/2017 - It seems that the console behaves differently on some systems
	// and I'm unsure why this is. It could be to do with windows default settings, or
	// screen resolutions, or system languages. Unfortunately, MSDN does not offer much
	// by way of useful information, and so the resulting sequence is the reult of experiment
	// that seems to work in multiple cases.
	//
	// The problem seems to be that the SetConsoleXXX functions are somewhat circular and 
	// fail depending on the state of the current console properties, i.e. you can't set
	// the buffer size until you set the screen size, but you can't change the screen size
	// until the buffer size is correct. This coupled with a precise ordering of calls
	// makes this procedure seem a little mystical :-P. Thanks to wowLinh for helping - Jx9

	// Change console visual size to a minimum so ScreenBuffer can shrink
	// below the actual visual size
	m_rectWindow = { 0, 0, 1, 1 };
	SetConsoleWindowInfo(m_hConsole, TRUE, &m_rectWindow);

	// Set the size of the screen buffer
	COORD coord = { (short)m_nScreenWidth, (short)m_nScreenHeight };
	if (!SetConsoleScreenBufferSize(m_hConsole, coord))
		Error(L"SetConsoleScreenBufferSize");

	// Assign screen buffer to the console
	if (!SetConsoleActiveScreenBuffer(m_hConsole))
		return Error(L"SetConsoleActiveScreenBuffer");

	// Set the font size now that the screen buffer has been assigned to the console
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = fontw;
	cfi.dwFontSize.Y = fonth;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;

	wcscpy_s(cfi.FaceName, L"Consolas");
	if (!SetCurrentConsoleFontEx(m_hConsole, false, &cfi))
		return Error(L"SetCurrentConsoleFontEx");


	// Set Physical Console Window Size
	m_rectWindow = { 0, 0, (short)(m_nScreenWidth - 1), (short)(m_nScreenHeight - 1) };
	if (!SetConsoleWindowInfo(m_hConsole, TRUE, &m_rectWindow))
		return Error(L"SetConsoleWindowInfo");

	//Disable Cursor
	CONSOLE_CURSOR_INFO ConCurInf;
	ConCurInf.dwSize = 10;
	ConCurInf.bVisible = FALSE;


	//Disable Maximize
	HWND consoleWindow = GetConsoleWindow();
	HMENU systemMenu = GetSystemMenu(consoleWindow, false);
	DeleteMenu(systemMenu, SC_MAXIMIZE, MF_BYCOMMAND);
	SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_SIZEBOX);

	//Disable Quick Edit
	SetConsoleMode(m_hConsoleIn, ~ENABLE_QUICK_EDIT_MODE);

	SetConsoleCursorInfo(m_hConsole, &ConCurInf);

	// Allocate memory for screen buffer
	m_bufScreen = new CHAR_INFO[m_nScreenWidth * m_nScreenHeight];
	memset(m_bufScreen, 0, sizeof(CHAR_INFO) * m_nScreenWidth * m_nScreenHeight);

	//Allocate memory for collision matrix
	collisionMatrix = new bool[m_nScreenWidth * m_nScreenHeight];
	memset(collisionMatrix, 0, sizeof(bool) * m_nScreenHeight * m_nScreenWidth);
	
	SetConsoleCtrlHandler((PHANDLER_ROUTINE)CloseHandler, TRUE);
	return 1;
}

void GameEngine::Draw(int x, int y, short c, short col)
{
	if (x >= 0 && x < m_nScreenWidth && y >= 0 && y < m_nScreenHeight)
	{
		m_bufScreen[y * m_nScreenWidth + x].Char.UnicodeChar = c;
		m_bufScreen[y * m_nScreenWidth + x].Attributes = col;
	}
}

void GameEngine::Fill(int x1, int y1, int x2, int y2, short c, short col)
{
	Clip(x1, y1);
	Clip(x2, y2);
	for (int x = x1; x <= x2; x++)
		for (int y = y1; y <= y2; y++)
			Draw(x, y, c, col);
}

void GameEngine::DrawString(int x, int y, std::wstring c, short col)
{
	for (size_t i = 0; i < c.size(); i++)
	{
		m_bufScreen[y * m_nScreenWidth + x + i].Char.UnicodeChar = c[i];
		m_bufScreen[y * m_nScreenWidth + x + i].Attributes = col;
	}
}

void GameEngine::DrawStringAlpha(int x, int y, std::wstring c, short col )
{
	for (size_t i = 0; i < c.size(); i++)
	{
		if (c[i] != L' ')
		{
			m_bufScreen[y * m_nScreenWidth + x + i].Char.UnicodeChar = c[i];
			m_bufScreen[y * m_nScreenWidth + x + i].Attributes = col;
		}
	}
}

void GameEngine::Clip(int& x, int& y)
{
	if (x < 0) x = 0;
	if (x >= m_nScreenWidth) x = m_nScreenWidth;
	if (y < 0) y = 0;
	if (y >= m_nScreenHeight) y = m_nScreenHeight;
}

void GameEngine::DrawLine(int x1, int y1, int x2, int y2, short c, short col)
{
	int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;
	dx = x2 - x1; dy = y2 - y1;
	dx1 = abs(dx); dy1 = abs(dy);
	px = 2 * dy1 - dx1;	py = 2 * dx1 - dy1;
	if (dy1 <= dx1)
	{
		if (dx >= 0)
		{
			x = x1; y = y1; xe = x2;
		}
		else
		{
			x = x2; y = y2; xe = x1;
		}

		Draw(x, y, c, col);

		for (i = 0; x < xe; i++)
		{
			x = x + 1;
			if (px < 0)
				px = px + 2 * dy1;
			else
			{
				if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) y = y + 1; else y = y - 1;
				px = px + 2 * (dy1 - dx1);
			}
			Draw(x, y, c, col);
		}
	}
	else
	{
		if (dy >= 0)
		{
			x = x1; y = y1; ye = y2;
		}
		else
		{
			x = x2; y = y2; ye = y1;
		}

		Draw(x, y, c, col);

		for (i = 0; y < ye; i++)
		{
			y = y + 1;
			if (py <= 0)
				py = py + 2 * dx1;
			else
			{
				if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) x = x + 1; else x = x - 1;
				py = py + 2 * (dx1 - dy1);
			}
			Draw(x, y, c, col);
		}
	}
}

void GameEngine::ClearCollsionMatrix() {
	memset(collisionMatrix, 0, sizeof(bool) * m_nScreenHeight * m_nScreenWidth);
}

void GameEngine::SetCollisionMatrix(int x, int y, bool state) {
	if (x >= 0 && x < m_nScreenWidth && y >= 0 && y < m_nScreenHeight)
	{
		collisionMatrix[y * m_nScreenWidth + x] = state;
	}
}

void GameEngine::FillCollisionMatrix(int x1, int y1, int x2, int y2, bool state) {
	Clip(x1, y1);
	Clip(x2, y2);
	for (int x = x1; x <= x2; x++)
		for (int y = y1; y <= y2; y++)
			SetCollisionMatrix(x, y, state);
}

bool GameEngine::CheckCollision(int x, int y) {
	return collisionMatrix[y * m_nScreenWidth + x];
}

void GameEngine::UpdateCollisionMatrix() {

}


GameEngine::~GameEngine()
{
	SetConsoleActiveScreenBuffer(m_hOriginalConsole);
	delete[] m_bufScreen;
}



void GameEngine::Start()
{
	// Start the thread
	m_bAtomActive = true;
	std::thread t = std::thread(&GameEngine::GameThread, this);

	// Wait for thread to be exited
	t.join();
}
void GameEngine::GameThread()
{
	// Create user resources as part of this thread
	if (!OnUserCreate())
		m_bAtomActive = false;

	auto tp1 = std::chrono::system_clock::now();
	auto tp2 = std::chrono::system_clock::now();

	while (m_bAtomActive)
	{
		while (m_bAtomActive)
		{
			// Handle Timing
			tp2 = std::chrono::system_clock::now();
			std::chrono::duration<float> elapsedTime = tp2 - tp1;
			tp1 = tp2;
			float fElapsedTime = elapsedTime.count();

			// Handle Keyboard Input
			for (int i = 0; i < 256; i++)
			{
				m_keyNewState[i] = GetAsyncKeyState(i);

				m_keys[i].bPressed = false;
				m_keys[i].bReleased = false;

				if (m_keyNewState[i] != m_keyOldState[i])
				{
					//https://stackoverflow.com/questions/2746817/what-does-the-0x80-code-mean-when-referring-to-keyboard-controls
					if (m_keyNewState[i] & 0x8000)
					{
						m_keys[i].bPressed = !m_keys[i].bHeld;
						m_keys[i].bHeld = true;
					}
					else
					{
						m_keys[i].bReleased = true;
						m_keys[i].bHeld = false;
					}
				}

				m_keyOldState[i] = m_keyNewState[i];
			}


			// Handle Frame Update
			if (!OnUserUpdate(fElapsedTime))
				m_bAtomActive = false;

			// Update Title & Present Screen Buffer
			wchar_t s[256];
			swprintf_s(s, 256, L"Crossing Road - Group 6 - FPS: %3.2f", 1.0f / fElapsedTime);
			SetConsoleTitle(s);

			WriteConsoleOutput(m_hConsole, m_bufScreen, { (short)m_nScreenWidth, (short)m_nScreenHeight }, { 0,0 }, &m_rectWindow);
		}


		// Allow the user to free resources if they have overrided the destroy function
		if (OnUserDestroy())
		{
			// User has permitted destroy, so exit and clean up
			m_cvGameFinished.notify_one();
		}
		else
		{
			// User denied destroy for some reason, so continue running
			m_bAtomActive = true;
		}
	}
}


int GameEngine::ScreenWidth()
{
	return m_nScreenWidth;
}
int GameEngine::ScreenHeight()
{
	return m_nScreenHeight;
}



	// Optional for clean up 
bool GameEngine::OnUserDestroy() { return true; }



GameEngine::sKeyState GameEngine::GetKey(int nKeyID) { return m_keys[nKeyID]; }
bool GameEngine::IsFocused() { return m_bConsoleInFocus; }


	//DEBUGGER
int GameEngine::Error(const wchar_t* msg)
{
	wchar_t buf[256];
	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), buf, 256, NULL);
	SetConsoleActiveScreenBuffer(m_hOriginalConsole);
	wprintf(L"ERROR: %s\n\t%s\n", msg, buf);
	return 0;
}
BOOL GameEngine::CloseHandler(DWORD evt)
{
	// Note this gets called in a seperate OS thread, so it must
	// only exit when the game has finished cleaning up, or else
	// the process will be killed before OnUserDestroy() has finished
	if (evt == CTRL_CLOSE_EVENT)
	{
		m_bAtomActive = false;

		// Wait for thread to be exited
		std::unique_lock<std::mutex> ul(m_muxGame);
		m_cvGameFinished.wait(ul);
	}
	return true;
}


// Define our static variables
std::atomic<bool> GameEngine::m_bAtomActive(false);
std::condition_variable GameEngine::m_cvGameFinished;
std::mutex GameEngine::m_muxGame;