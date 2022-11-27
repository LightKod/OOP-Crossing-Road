#pragma once
#ifndef _STATE_CREDIT_H_
#define _STATE_CREDIT_H_
#include "CrossingRoadGame.h"

class StateCredit : public CrossingRoadGame::State
{
public:
	virtual bool Update(float fElapsedTime);
	virtual bool OnStateEnter();
	virtual bool OnStateExit();

	StateCredit(CrossingRoadGame* game) : State(game) {};

protected:
	void CloseProjectorScreen();

	void InstroduceMember();
	void ClearOldName(const int& _x0, const int& _x1,
		const short& fg, const short& bg);
	void MEMBERS(const int& x, const int& y,
		const short& fg, const short& bg);
	void NGUYEN_NHAT_QUANG(const int& x, const int& y,
		const short& fg, const short& bg);
	void VU_MINH_PHAT(const int& x, const int& y,
		const short& fg, const short& bg);
	void NGUYEN_NGOC_VU(const int& x, const int& y,
		const short& fg, const short& bg);
	void TRAN_DINH_TRUNG(const int& x, const int& y,
		const short& fg, const short& bg);

	void InstroduceInstructor();
	void INSTRUCTOR(const int& x, const int& y,
		const short& fg, const short& bg);
	void TRUONG_TOAN_THINH(const int& x, const int& y,
		const short& fg, const short& bg);

	void Introduction();
	void A_PROJECT(const int& x, const int& y,
		const short& fg, const short& bg);
	void FROM_TEAM6(const int& x, const int& y,
		const short& fg, const short& bg);

	void DrawProjectorScreen();
	void ProjectorScreenFrame();
	void ProjectorScreen1();
	void ProjectorScreen2();
	void ProjectorScreen3();
	void ProjectorScreen4();

	void A(const int& x, const int& y,
		const short& fg, const short& bg);
	void P(const int& x, const int& y,
		const short& fg, const short& bg);
	void R(const int& x, const int& y,
		const short& fg, const short& bg);
	void O(const int& x, const int& y,
		const short& fg, const short& bg);
	void J(const int& x, const int& y,
		const short& fg, const short& bg);
	void E(const int& x, const int& y,
		const short& fg, const short& bg);
	void C(const int& x, const int& y,
		const short& fg, const short& bg);
	void T(const int& x, const int& y,
		const short& fg, const short& bg);
	void F(const int& x, const int& y,
		const short& fg, const short& bg);
	void M(const int& x, const int& y,
		const short& fg, const short& bg);
	void _6(const int& x, const int& y,
		const short& fg, const short& bg);
	void U(const int& x, const int& y,
		const short& fg, const short& bg);
	void N(const int& x, const int& y,
		const short& fg, const short& bg);
	void G(const int& x, const int& y,
		const short& fg, const short& bg);
	void H(const int& x, const int& y,
		const short& fg, const short& bg);
	void I(const int& x, const int& y,
		const short& fg, const short& bg);
	void S(const int& x, const int& y,
		const short& fg, const short& bg);
	void B(const int& x, const int& y,
		const short& fg, const short& bg);
	void Y(const int& x, const int& y,
		const short& fg, const short& bg);
	void Q(const int& x, const int& y,
		const short& fg, const short& bg);
	void V(const int& x, const int& y,
		const short& fg, const short& bg);
	void D(const int& x, const int& y,
		const short& fg, const short& bg);

private:
	void SoundThread();
	
	Sound CreditSound;
	bool m_bBack{ false };
	bool m_Start{ false };

	static const int M_S_SRC_X0;
	static const int M_S_SRC_X1;
	static const int M_S_SRC_Y0;
	static const int M_S_SRC_Y1;

};

#endif // !_STATE_CREDIT_H_
