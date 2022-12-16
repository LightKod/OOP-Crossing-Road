#include "StateMenu.h"
#include "StatePlay.h"
#include "StatePlay_Deadline.h"
#include "StatePlay_Versus.h"
#include "StatePlay_Endless.h"
#include "StateLoad.h"
#include "StateLB.h"
#include "StateSetting.h"
#include "StateCredit.h"
#include "StateExit.h"
#include "Menu.h"
#include "StateChoosePlayMode.h"

#define TIME_LIMIT 10.f
#define TIME_FACTOR 51.f

int		StateMenu::m_s_OptionIdx = 0;
float	StateMenu::m_s_DeltaTime = 0.f;

bool StateMenu::Update(float fElapsedTime) {
	static const int MAX_OPT = 6;
	// Update current time
	WaitSndTm += fElapsedTime * TIME_FACTOR;
	this->m_s_DeltaTime += fElapsedTime;

	// Xử lý chuyển state
	if (game->GetKey(VK_SPACE).bPressed) {
		// Hiệu ứng chuyển state
		this_thread::yield();
		Sound::PlayEnterSound();

		p_Menu->SplashAnimation(game, this->m_s_OptionIdx);

		// Tạo state mới
		switch (this->m_s_OptionIdx) {
		case 0 :
			//game->SetState(new StatePlay(game));
			game->SetState(new StateChoosePlayMode(game));
			break;
		case 1 : 
			game->SetState(new StateLoad(game));
			break;
		case 2 :
			game->SetState(new StateLB(game));
			break;
		case 3 :
			game->SetState(new StateSetting(game));
			break;
		case 4 :
			game->SetState(new StateCredit(game));
			break;
		case 5 :
			game->SetState(new StateExit(game));
			break;
		default:
			break;
		}
		
		Sound::CloseMenuSelectSound();
		Sound::CloseEnterSound();
		return 1;
	}
	
	if (game->GetKey(VK_D).bPressed) {
		game->SetState(new StatePlay_Deadline(game));
		Sound::CloseMenuSelectSound();
		return true;
	}
	if (game->GetKey(VK_E).bPressed) {
		game->SetState(new StatePlay_Endless(game));
		Sound::CloseMenuSelectSound();
		return true;
	}
	if (game->GetKey(L'V').bPressed) {
		game->SetState(new StatePlay_Versus(game));
		Sound::CloseMenuSelectSound();
		return true;
	}

	// Xử lý tương tác với người dùng
	if (game->GetKey(VK_W).bPressed) {
		m_s_OptionIdx = (m_s_OptionIdx - 1 + MAX_OPT) % MAX_OPT;
		isClicked = 1;
		WaitSndTm = 0.f;
		DrawMainMenu();

		//this_thread::yield();
		//Sound::PlayMenuSelectSound();
		
		return 1;
	}
	if (game->GetKey(VK_S).bPressed) {
		m_s_OptionIdx = (m_s_OptionIdx + 1) % MAX_OPT;
		isClicked = 1;
		WaitSndTm = 0.f;
		DrawMainMenu();

		//this_thread::yield();
		//Sound::PlayMenuSelectSound();
		
		return 1;
	}

	//Sleep(1);
	if (WaitSndTm >= TIME_LIMIT && isClicked) {
		this_thread::yield();
		Sound::PlayMenuSelectSound();
		isClicked = 0;
		WaitSndTm = 0.f;
	}

	// Xử lý đồ họa main menu
	DrawMainMenu();
	return true;
}
bool StateMenu::OnStateEnter() {
	this->game = game;
	DrawMainMenu();
	return true;
}
bool StateMenu::OnStateExit() {
	return true;
}

void StateMenu::DrawMainMenu() {
	if (this->m_s_DeltaTime > .5f) {
		this->m_s_DeltaTime = 0.f;
		down = !down;

		p_Menu->UpdateMenuUI(game, this->m_s_OptionIdx, 0, 0);
		return;
	}

	if (this->down)
		p_Menu->UpdateMenuUI(game, this->m_s_OptionIdx, 0, 0);
	else
		p_Menu->UpdateMenuUI(game, this->m_s_OptionIdx, 1, 0);
}

StateMenu::StateMenu(CrossingRoadGame* game) : State(game) {
	if (!p_Menu)
		p_Menu = new Menu(game);
	Sound::OpenMenuSelectSound();
	Sound::OpenEnterSound();
};
StateMenu::~StateMenu() {
	if (p_Menu) {
		delete p_Menu;
		p_Menu = nullptr;
	}
}
