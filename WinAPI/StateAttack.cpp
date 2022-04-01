#include "Stdafx.h"
#include "StateAttack.h"
#include "Player.h"


// 무기별 콤보, 스킬공격 2종 
//OneHandWeaponCombo* OneHandWeaponCombo::instance;
//TwoHandWeaponCombo* TwoHandWeaponCombo::instance;
//SoulCapture* SoulCapture::instance;
//SpearStrike* SpearStrike::instance;

#if 0
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
	combo.reset(0);


	player->setPlayerImg(IMG("p_oneHandCombo"));


	timeCount = 0;

	// 방향별 무기 프레임 지정(comboOne 1,2 /  comboTwo 1,2 / comboThree 1,2 ) : 총 6개
	// 스위치로 플레이어 방향 받아서 지정.

}

void OneHandWeaponCombo::stateUpdate(Player* player)
{
	// 30카운트(0.5초)지나기 전 재입력하면 다음콤보
	timeCount++;
	if (combo.none())
	{
		combo.set(0);
		comboOne(player);
	}

	// 좌
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		player->setPlayerPosX(player->getPlayerPosX() - player->getPlayerSpeed());
		player->setPlayerDirection(PLAYERDIRECTION::LEFT);

		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			player->setPlayerDirection(PLAYERDIRECTION::LEFTUP);
		}
		if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			player->setPlayerDirection(PLAYERDIRECTION::LEFTDOWN);
		}
	}
	// 우
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		player->setPlayerPosX(player->getPlayerPosX() + player->getPlayerSpeed());
		player->setPlayerDirection(PLAYERDIRECTION::RIGHT);

		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			player->setPlayerDirection(PLAYERDIRECTION::RIGHTUP);
		}
		if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			player->setPlayerDirection(PLAYERDIRECTION::RIGHTDOWN);
		}
	}
	// 위
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		player->setPlayerPosY(player->getPlayerPosY() - player->getPlayerSpeed());
		player->setPlayerDirection(PLAYERDIRECTION::UP);


		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			player->setPlayerDirection(PLAYERDIRECTION::LEFTUP);
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			player->setPlayerDirection(PLAYERDIRECTION::RIGHTUP);
		}
	}
	// 아래
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		player->setPlayerPosY(player->getPlayerPosY() + player->getPlayerSpeed());
		player->setPlayerDirection(PLAYERDIRECTION::DOWN);


		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			player->setPlayerDirection(PLAYERDIRECTION::LEFTDOWN);
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			player->setPlayerDirection(PLAYERDIRECTION::RIGHTDOWN);
		}
	}

	if (combo.test(0) && KEYMANAGER->isStayKeyDown('X') && !player->getIsStateCheck().test(2))
	{
		// 2단 공격 실행
		combo.set(1);
		comboTwo(player);
		combo.reset(0);
	}
	else if (combo.test(1) && KEYMANAGER->isStayKeyDown('X') && !player->getIsStateCheck().test(2))
	{
		// 3단 공격 실행
		combo.set(2);
		comboThree(player);
		combo.reset(1);
	}
	//프레임 종료 or 카운트 끝나면 대기모션으로 전환)
	if (combo.test(2) && (timeCount >= 30 && !player->getIsStateCheck().test(2)))
	{
		SetPlayerState(player, IdleState::getInstance());
		combo.reset();
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

void OneHandWeaponCombo::comboOne(Player* player)
{
	player->getIsStateCheck().set(2);
	cout << "한손무기 1단 공격 함수" << endl;
	if (combo.test(0)) cout << "1단공격 비트셋 킴" << endl;

	player->setPlayerFrameX(player->getPlayerFrameX() + 1);
	if (player->getPlayerFrameX() == 1 && timeCount % 30 == 0)
	{
		//프레임처리까지 다아아아 끝나고 공격처리 끝 
		player->getIsStateCheck().reset(2);
	}

}

void OneHandWeaponCombo::comboTwo(Player* player)
{
	player->getIsStateCheck().set(2);

	cout << "한손무기 2단 공격 함수" << endl;

	player->setPlayerFrameX(player->getPlayerFrameX() + 1);
	if (player->getPlayerFrameX() == 3 && timeCount % 30 == 0)
	{
		//프레임처리까지 다아아아 끝나고 공격처리 끝 
		player->getIsStateCheck().reset(2);
	}

}

void OneHandWeaponCombo::comboThree(Player* player)
{
	player->getIsStateCheck().set(2);

	cout << "한손무기 3단 공격 함수" << endl;

	player->setPlayerFrameX(player->getPlayerFrameX() + 1);
	if (player->getPlayerFrameX() == 1 && timeCount % 30 == 0)
	{
		//프레임처리까지 다아아아 끝나고 공격처리 끝 
		player->getIsStateCheck().reset(2);
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
#endif 