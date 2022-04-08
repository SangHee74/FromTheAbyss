#include "Stdafx.h"
#include "StateBase.h"
#include "StateAttack.h"
#include "Player.h"

// 무기별 콤보, 스킬공격 2종 
OneHandWeaponCombo* OneHandWeaponCombo::instance;
TwoHandWeaponCombo* TwoHandWeaponCombo::instance;
//SoulCapture* SoulCapture::instance;
//SpearStrike* SpearStrike::instance;

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

	player->getPlayerCollisionRc().attEffFrameX = 0;
	player->getPlayerCollisionRc().attEffFrameY = 0;
	
	combo.reset(0);

	timeCount = 0;

	// 방향별 무기 프레임 지정(comboOne 1,2 /  comboTwo 1,2 / comboThree 1,2 ) : 총 6개
	// 스위치로 플레이어 방향 받아서 지정.

}

void OneHandWeaponCombo::stateUpdate(Player* player)
{

	// 60카운트(1초)지나기 전 재입력하면 다음콤보
	// 콤보에서 시간초 초기화.
	timeCount++;

	// 1단 공격 실행
	combo.set(0);
	if (combo.none()) comboOne(player);
	


	//if (combo.test(0) && KEYMANAGER->isStayKeyDown('X') && !player->getIsStateCheck().test(2))
	{
		// 2단 공격 실행
		//combo.set(1);
		//comboTwo(player);
		//combo.reset(0);
	}
	//else if (combo.test(1) && KEYMANAGER->isStayKeyDown('X') && !player->getIsStateCheck().test(2))
	{
		// 3단 공격 실행
		//combo.set(2);
		//comboThree(player);
		//combo.reset(1);
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
	//if (instance)
	//{
	//	delete instance;
	//	instance = 0;
	//}
}

void OneHandWeaponCombo::stateRender(Player* player)
{
}

void OneHandWeaponCombo::comboOne(Player* player)
{
	
	player->getPlayer().image = IMG("p_oneHandCombo_01");
	player->getPlayerCollisionRc().attEffectImg = IMG("eff_sword");
	player->getPlayerCollisionRc().attEffFrameY = static_cast<int>(player->getDirection());

	// isAttack
	cout << "한손무기 1단 공격 함수" << endl;
	player->setPlayerCollisionAttRc(0, 0, 0, 0);

	if (timeCount % 120 == 0)
	{
		player->getPlayer().frameX += 1;

		if (player->getPlayer().frameX > 1 && timeCount % 180 == 0)
		{
			//프레임처리까지 다아아아 끝나고 공격처리 끝 
			player->getIsStateCheck().reset(2);
		}
	}


}

void OneHandWeaponCombo::comboTwo(Player* player)
{
	player->getPlayer().image = IMG("p_oneHandCombo_02");

	player->getIsStateCheck().set(2);

	cout << "한손무기 2단 공격 함수" << endl;

	player->getPlayer().frameX += 1;
	if (player->getPlayer().frameX == 3 && timeCount % 60 == 0)
	{
		//프레임처리까지 다아아아 끝나고 공격처리 끝 
		player->getIsStateCheck().reset(2);
	}

}

void OneHandWeaponCombo::comboThree(Player* player)
{
	player->getPlayer().image = IMG("p_oneHandCombo_03");

	player->getIsStateCheck().set(2);

	cout << "한손무기 3단 공격 함수" << endl;

	player->getPlayer().frameX += 1;
	if (player->getPlayer().frameX == 5 && timeCount % 60 == 0)
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

void TwoHandWeaponCombo::stateInit(Player* player)
{
	// 비트셋 초기화 + 공격으로 전환
	player->getIsStateCheck().reset(0);
	player->getIsStateCheck().set(2);
	
	timeCount = 0;
}

void TwoHandWeaponCombo::stateUpdate(Player* player)
{

	// 30카운트(0.5초)지나기 전 재입력하면 다음콤보
	timeCount++;
	player->getPlayer().image = IMG("p_oneHandCombo_02");

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

void TwoHandWeaponCombo::stateRender(Player* player)
{
}

#if 0
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
	//	if (_player.frameX > 1 ) _player.frameX = 0;

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
	//	if (_player.frameX > 1) _player.frameX = 0;

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