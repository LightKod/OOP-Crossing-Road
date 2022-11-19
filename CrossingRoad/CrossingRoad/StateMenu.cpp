#include "StateMenu.h"
#include "StatePlay.h"
#include "StateLoad.h"
#include "StateLB.h"
#include "StateCredit.h"
#include "StateExit.h"
#include "Menu.h"

int		Menu::m_s_OptionIdx = 0;
float	Menu::m_s_DeltaTime = 0.f;

Menu* p_Menu = nullptr;

bool StateMenu::Update(float fElapsedTime) {
	static const int MAX_OPT = 6;

	// Update current time
	this->m_s_DeltaTime += fElapsedTime;

	// Xử lý chuyển state
	if (game->GetKey(VK_SPACE).bReleased) {
		// Hiệu ứng chuyển state
		p_Menu->SplashAnimation(game, this->m_s_OptionIdx);

		// Tạo state mới
		switch (this->m_s_OptionIdx) {
		case 0: 
			game->SetState(new StatePlay(game));
			break;
		case 1: 
			game->SetState(new StateLoad(game));
			break;
		case 2: 
			game->SetState(new StateLB(game));
			break;
			//case 3 : game->SetState(new StateSetting(game));
			break;
		case 4: game->SetState(new StateCredit(game));
			break;
		case 5: game->SetState(new StateExit(game));
			break;
		default: /*game->SetState(new StatePlay(game));*/
			break;
		}

		return 1;
	}

	// Xử lý tương tác với người dùng
	if (game->GetKey(VK_UP).bReleased) {
		m_s_OptionIdx = (m_s_OptionIdx - 1 + MAX_OPT) % MAX_OPT;
	}
	if (game->GetKey(VK_DOWN).bReleased) {
		m_s_OptionIdx = (m_s_OptionIdx + 1) % MAX_OPT;
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
};
StateMenu::~StateMenu() {
	if (p_Menu) {
		delete p_Menu;
		p_Menu = nullptr;
	}
}
