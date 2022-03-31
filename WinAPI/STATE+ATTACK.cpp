#include "Stdafx.h"
#include "STATE.h"


// 무기별 콤보, 스킬공격 2종 
OneHandWeaponCombo* OneHandWeaponCombo::instance;
TwoHandWeaponCombo* TwoHandWeaponCombo::instance;
SoulCapture* SoulCapture::instance;
SpearStrike* SpearStrike::instance;


// 공격
OneHandWeaponCombo* OneHandWeaponCombo::getInstance()
{
	if (instance == nullptr) instance = new OneHandWeaponCombo();
	return instance;
}

void OneHandWeaponCombo::stateInit(Player* player)
{
	// 비트셋 초기화 + 공격으로 전환
	player->getIsStateCheck().reset(0);
	player->getIsStateCheck().set(2);

	player->setPlayerImg(IMG("p_oneHandCombo"));

	// Y프레임만 세팅
	player->setPlayerFrameY(static_cast<int>(player->getPlayerDirection()));

}

void OneHandWeaponCombo::stateUpdate(Player* player)
{
	// 30카운트(0.5초)지나기 전 재입력하면 다음콤보
	timeCount++;

	cout << "한손무기 1단 공격" << endl;
	if ( KEYMANAGER->isStayKeyDown('X'))
	{
		// 2단 공격 실행

	}
	//프레임 종료 or 카운트 끝나면 대기모션으로 전환)
	if ( KEYOKU('X') && timeCount >= 30)
	{
		SetPlayerState(player, IdleState::getInstance());
	}

}

void OneHandWeaponCombo::stateRelease()
{
	if (instance)
	{
		delete instance;
		instance = 0;
	}
}


TwoHandWeaponCombo * TwoHandWeaponCombo::getInstance()
{
	if (instance == nullptr) instance = new TwoHandWeaponCombo();
	return instance;
}

void TwoHandWeaponCombo::stateInit(Player * player)
{
	// 비트셋 초기화 + 공격으로 전환
	player->getIsStateCheck().reset(0);
	player->getIsStateCheck().set(2);

	player->setPlayerImg(IMG("p_twoHandCombo"));

	// Y프레임만 세팅
	player->setPlayerFrameY(static_cast<int>(player->getPlayerDirection()));
}

void TwoHandWeaponCombo::stateUpdate(Player * player)
{
	// 30카운트(0.5초)지나기 전 재입력하면 다음콤보
	timeCount++;

	cout << "두손무기 1단 공격" << endl;
	if (KEYMANAGER->isStayKeyDown('X'))
	{
		// 2단 공격 실행

	}
	//프레임 종료 or 카운트 끝나면 대기모션으로 전환)
	if (KEYOKU('X') && timeCount >= 30)
	{
		SetPlayerState(player, IdleState::getInstance());
	}
}

void TwoHandWeaponCombo::stateRelease()
{
	if (instance)
	{
		delete instance;
		instance = 0;
	}
}


// 스킬 =========================================================
SoulCapture* SoulCapture::getInstance()
{
	if (instance == nullptr) instance = new SoulCapture();
	return instance;
}

void SoulCapture::stateInit(Player * player)
{
	// 비트셋 초기화 + 공격으로 전환
	player->getIsStateCheck().reset(0);
	player->getIsStateCheck().set(2);

	player->setPlayerImg(IMG("p_skill_soulCapture"));

	// Y프레임만 세팅
	player->setPlayerFrameY(static_cast<int>(player->getPlayerDirection()));
}

void SoulCapture::stateUpdate(Player * player)
{
	// 30카운트(0.5초)지나기 전 재입력하면 다음콤보
	timeCount++;

	cout << "스킬 : 소울캡쳐 시작 " << endl;
	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		// X키 연타시 소울캡쳐 데미지 바 조정
	}

	// 소울 캡쳐 종료시(수정필요)
	if (KEYOKU('X') && timeCount >= 30)
	{
		SetPlayerState(player, IdleState::getInstance());
	}
}

void SoulCapture::stateRelease()
{
	if (instance)
	{
		delete instance;
		instance = 0;
	}
}



SpearStrike * SpearStrike::getInstance()
{
	if (instance == nullptr) instance = new SpearStrike();
	return instance;
}

void SpearStrike::stateInit(Player * player)
{
	// 수정필요~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// 비트셋 초기화 + 공격으로 전환
	player->getIsStateCheck().reset(0);
	player->getIsStateCheck().set(2);

	player->setPlayerImg(IMG("p_skill_soulCapture"));

	// Y프레임만 세팅
	player->setPlayerFrameY(static_cast<int>(player->getPlayerDirection()));
}

void SpearStrike::stateUpdate(Player * player)
{
}

void SpearStrike::stateRelease()
{
	if (instance)
	{
		delete instance;
		instance = 0;
	}
}

