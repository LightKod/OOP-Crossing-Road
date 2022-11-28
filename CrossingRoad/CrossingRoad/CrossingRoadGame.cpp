#pragma once
#include "CrossingRoadGame.h"
#include "Road.h"
#include "River.h"
#include "Frog.h"
#include "StateMenu.h"
int optionIndex = 0;
static CrossingRoadGame::State* state;
int CrossingRoadGame::s_CharIdx = 0;

bool CrossingRoadGame::OnUserCreate()
{
	SetState(new StateMenu(this));
	return true;
}


bool CrossingRoadGame::OnUserUpdate(float fElapsedTime)
{
	if (state != nullptr) {
		return state->Update(fElapsedTime);
	}
	return true;
}

void CrossingRoadGame::State::char2Pixel(const wchar_t& ch, const int& x,
	const int& y, const int& fg, const int& bg, int& offsetX)
{
	vector<wstring> Strings(3);

	switch (ch) {
	case L'Q': case L'q':
		Strings[0] = L"█▀▀█";
		Strings[1] = L"█  █";
		Strings[2] = L"▀▀█▄";
		offsetX += 5;
		break;
	case L'W': case L'w':
		Strings[0] = L"█   █";
		Strings[1] = L"█ █ █";
		Strings[2] = L"█▄▀▄█";
		offsetX += 6;
		break;
	case L'E': case L'e':
		Strings[0] = L"█▀▀▀";
		Strings[1] = L"█▀▀▀";
		Strings[2] = L"█▄▄▄";
		offsetX += 5;
		break;
	case L'R': case L'r':
		Strings[0] = L"█▀▀█";
		Strings[1] = L"█▄▄▀";
		Strings[2] = L"█  █";
		offsetX += 5;
		break;
	case L'T': case L't':
		Strings[0] = L"▀▀█▀▀";
		Strings[1] = L"  █  ";
		Strings[2] = L"  █  ";
		offsetX += 6;
		break;
	case L'Y': case L'y':
		Strings[0] = L"█   █";
		Strings[1] = L"█▄▄▄█";
		Strings[2] = L"  █  ";
		offsetX += 6;
		break;
	case L'U': case L'u':
		Strings[0] = L"█  █";
		Strings[1] = L"█  █";
		Strings[2] = L"▀▄▄▀";
		offsetX += 5;
		break;
	case L'I': case L'i':
		Strings[0] = L"▀█▀";
		Strings[1] = L" █ ";
		Strings[2] = L"▄█▄";
		offsetX += 4;
		break;
	case L'O': case L'o':
		Strings[0] = L"█▀▀█";
		Strings[1] = L"█  █";
		Strings[2] = L"█▄▄█";
		offsetX += 5;
		break;
	case L'P': case L'p':
		Strings[0] = L"█▀▀█";
		Strings[1] = L"█▄▄█";
		Strings[2] = L"█   ";
		offsetX += 5;
		break;
	case L'A': case L'a':
		Strings[0] = L"█▀▀█";
		Strings[1] = L"█▄▄█";
		Strings[2] = L"█  █";
		offsetX += 5;
		break;
	case L'S': case L's':
		Strings[0] = L"█▀▀▀█";
		Strings[1] = L"▀▀▀▄▄";
		Strings[2] = L"█▄▄▄█";
		offsetX += 6;
		break;
	case L'D': case L'd':
		Strings[0] = L"█▀▀▄";
		Strings[1] = L"█  █";
		Strings[2] = L"█▄▄▀";
		offsetX += 5;
		break;
	case L'F': case L'f':
		Strings[0] = L"█▀▀▀";
		Strings[1] = L"█▀▀▀";
		Strings[2] = L"█   ";
		offsetX += 5;
		break;
	case L'G': case L'g':
		Strings[0] = L"█▀▀█";
		Strings[1] = L"█ ▄▄";
		Strings[2] = L"█▄▄█";
		offsetX += 5;
		break;
	case L'H': case L'h':
		Strings[0] = L"█  █";
		Strings[1] = L"█▀▀█";
		Strings[2] = L"█  █";
		offsetX += 5;
		break;
	case L'J': case L'j':
		Strings[0] = L"   █";
		Strings[1] = L"▄  █";
		Strings[2] = L"█▄▄█";
		offsetX += 5;
		break;
	case L'K': case L'k':
		Strings[0] = L"█ ▄▀";
		Strings[1] = L"█▀▄ ";
		Strings[2] = L"█  █";
		offsetX += 5;
		break;
	case L'L': case L'l':
		Strings[0] = L"█   ";
		Strings[1] = L"█   ";
		Strings[2] = L"█▄▄█";
		offsetX += 5;
		break;
	case L'Z': case L'z':
		Strings[0] = L"█▀▀▀█";
		Strings[1] = L"▄▄▄▀▀";
		Strings[2] = L"█▄▄▄█";
		offsetX += 6;
		break;
	case L'X': case L'x':
		Strings[0] = L"▀▄ ▄▀";
		Strings[1] = L"  █  ";
		Strings[2] = L"▄▀ ▀▄";
		offsetX += 6;
		break;
	case L'C': case L'c':
		Strings[0] = L"█▀▀█";
		Strings[1] = L"█   ";
		Strings[2] = L"█▄▄█";
		offsetX += 5;
		break;
	case L'V': case L'v':
		Strings[0] = L"█   █";
		Strings[1] = L" █ █ ";
		Strings[2] = L" ▀▄▀ ";
		offsetX += 6;
		break;
	case L'B': case L'b':
		Strings[0] = L"█▀▀█";
		Strings[1] = L"█▀▀▄";
		Strings[2] = L"█▄▄█";
		offsetX += 5;
		break;
	case L'N': case L'n':
		Strings[0] = L"█▄  █";
		Strings[1] = L"█ █ █";
		Strings[2] = L"█  ▀█";
		offsetX += 6;
		break;
	case L'M': case L'm':
		Strings[0] = L"█▀▄▀█";
		Strings[1] = L"█ █ █";
		Strings[2] = L"█   █";
		offsetX += 6;
		break;
	case L'1':
		Strings[0] = L"▄█ ";
		Strings[1] = L" █ ";
		Strings[2] = L"▄█▄";
		offsetX += 4;
		break;
	case L'2':
		Strings[0] = L"█▀█";
		Strings[1] = L" ▄▀";
		Strings[2] = L"█▄▄";
		offsetX += 4;
		break;
	case L'3':
		Strings[0] = L"█▀▀█";
		Strings[1] = L"  ▀▄";
		Strings[2] = L"█▄▄█";
		offsetX += 5;
		break;
	case L'4':
		Strings[0] = L"▄▀█ ";
		Strings[1] = L"█▄█▄";
		Strings[2] = L"  █ ";
		offsetX += 5;
		break;
	case L'5':
		Strings[0] = L"█▀▀";
		Strings[1] = L"▀▀▄";
		Strings[2] = L"▄▄▀";
		offsetX += 4;
		break;
	case L'6':
		Strings[0] = L"▄▀▀▄";
		Strings[1] = L"█▄▄ ";
		Strings[2] = L"▀▄▄▀";
		offsetX += 5;
		break;
	case L'7':
		Strings[0] = L"▀▀▀█";
		Strings[1] = L"  █ ";
		Strings[2] = L" ▐▌ ";
		offsetX += 5;
		break;
	case L'8':
		Strings[0] = L"▄▀▀▄";
		Strings[1] = L"▄▀▀▄";
		Strings[2] = L"▀▄▄▀";
		offsetX += 5;
		break;
	case L'9':
		Strings[0] = L"▄▀▀▄";
		Strings[1] = L"▀▄▄█";
		Strings[2] = L" ▄▄▀";
		offsetX += 5;
		break;
	case L'0':
		Strings[0] = L"█▀▀█";
		Strings[1] = L"█▄▀█";
		Strings[2] = L"█▄▄█";
		offsetX += 5;
		break;
	case L'/':
		Strings[0] = L"  ██";
		Strings[1] = L" ██";
		Strings[2] = L"██";
		offsetX += 5;
		break;
	case L' ':
		offsetX += 4;
		break;
	default:
		break;
	}

	game->DrawString(x, y, Strings[0], fg + bg);
	game->DrawString(x, y + 1, Strings[1], fg + bg);
	game->DrawString(x, y + 2, Strings[2], fg + bg);
}

void CrossingRoadGame::State::string2Pixel(const wstring& wStr, const int& x,
	const int& y, const int& fg, const int& bg)
{
	int offsetX = 0;
	for (const wchar_t& ch : wStr) {
		char2Pixel(ch, x + offsetX, y, fg, bg, offsetX);
	}
}