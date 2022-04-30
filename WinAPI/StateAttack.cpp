#include "Stdafx.h"
#include "StateBase.h"
#include "StateAttack.h"
#include "Player.h"

// 무기별 콤보,
OneHandWeaponCombo* OneHandWeaponCombo::instance;
TwoHandWeaponCombo* TwoHandWeaponCombo::instance;


// 공격
OneHandWeaponCombo* OneHandWeaponCombo::getInstance()
{
	if (instance == nullptr) instance = new OneHandWeaponCombo();
	return instance;
}

void OneHandWeaponCombo::stateInit(Player* player)
{
	// 플레이어 상태 비트셋 초기화 + 공격으로 전환
	player->getIsStateCheck().reset();
	player->getIsStateCheck().set(2);

	player->getState() =PLAYERSTATE::ATK_ONEHANDCOMBO;
	
	player->getPlayerCollisionRc().atkEffFrameX = 0;
	player->getPlayerCollisionRc().atkEffFrameY = 0;
	player->getPlayerCollisionRc().atkPosX = 0;
	player->getPlayerCollisionRc().atkPosY = 0;
	player->getPlayerCollisionRc().atkWidth = 0;
	player->getPlayerCollisionRc().atkHeight = 0;
	
	// 콤보 비트셋 초기화 + 1단 공격 실행
	_comboStart.reset();
	_comboStart.set(0);
	_comboEnd.reset(0);

	//_timeCount = 0;
	_comboInputMinTime = 0.0f;
	_comboInputMaxTime = 0.0f;
	_playerMotionTime = 0.0f;

}

void OneHandWeaponCombo::stateUpdate(Player* player)
{
	// 60카운트(1초)지나기 전 재입력하면 다음콤보
	// 콤보에서 시간초 초기화.

	_comboInputMaxTime += TIMEMANAGER->getElapsedTime();
	_comboInputMinTime += TIMEMANAGER->getElapsedTime();
	
	if (_comboStart.test(0)) comboOne(player);
	
	if ( _comboInputMinTime > 2.4f					 // 키입력 시간 초과
		 && !player->getIsStateCheck().test(2)    )  // 공격상태 아님
	{
		_comboStart.reset();
		_comboEnd.reset();

		SetPlayerState(player, IdleState::getInstance());
	}

	// 콤보 시간 중 타격범위 업데이트 여부 
	if (_playerMotionTime >= 0.9f && _playerMotionTime <= 1.0f) player->getPlayerCollisionRc().atkRangeUpdate = true;
	if (_playerMotionTime >= 1.8f) player->getPlayerCollisionRc().atkRangeUpdate = false;


	// 콤보-프레임 별 무기 프레임 업데이트 + 타격범위 업데이트
	player->playerAttSetting(_comboStart);					// 공격범위 업데이트 		
	
}

void OneHandWeaponCombo::stateRelease()
{

}

void OneHandWeaponCombo::stateRender(Player* player)
{
}

void OneHandWeaponCombo::comboOne(Player* player)
{
	// 이미지 세팅 
	player->getPlayer().image = IMG("p_oneHandCombo_01");

	// 프레임 세팅  
	// 1콤보 첫번째 프레임 
	if (_playerMotionTime <= 1.0f)
	{
		if (player->getIsStateCheck().test(0)) // L
		{
			_playerMotionTime+=TIMEMANAGER->getElapsedTime(); // 프레임이 있는 경우에만 증가
			player->getPlayer().frameX = 0;
		}
		if (!player->getIsStateCheck().test(0)) // R
		{
			_playerMotionTime += TIMEMANAGER->getElapsedTime();
			player->getPlayer().frameX = 1;						// 캐릭터 프레임
		}
	}

	// 1콤보 두번째 프레임
	if (_playerMotionTime >= 1.0f && _playerMotionTime <= 2.4f)
	{
		_comboInputMaxTime = 0;
		// 왼쪽이고, 콤보 1단 중임
		if (player->getIsStateCheck().test(0) && _comboStart.test(0)) // L
		{
			_playerMotionTime += TIMEMANAGER->getElapsedTime();
			player->getPlayer().frameX = 1;
		}
		// 오른쪽이고, 콤보 1단 중임
		if (!player->getIsStateCheck().test(0) && _comboStart.test(0)) // R 
		{
			_playerMotionTime += TIMEMANAGER->getElapsedTime();
			player->getPlayer().frameX = 0;
		}
	}

	if (_playerMotionTime >= 2.4f)			// 콤보 1단 모션이 모두 끝나면
	{
		_comboEnd.set(0);				    // 1단콤보 종료됨
		player->getIsStateCheck().reset(2); // 공격상태 꺼짐
	}

}

void OneHandWeaponCombo::comboTwo(Player* player)
{
	player->getPlayer().image = IMG("p_oneHandCombo_02");
	player->getIsStateCheck().set(2);

}

void OneHandWeaponCombo::comboThree(Player* player)
{
	player->getPlayer().image = IMG("p_oneHandCombo_03");
	player->getIsStateCheck().set(2);

}


TwoHandWeaponCombo * TwoHandWeaponCombo::getInstance()
{
	if (instance == nullptr) instance = new TwoHandWeaponCombo();
	return instance;
}

void TwoHandWeaponCombo::stateInit(Player* player)
{
	// 플레이어 상태 비트셋 초기화 + 공격으로 전환
	player->getIsStateCheck().reset();
	player->getIsStateCheck().set(2);

	player->getState() = PLAYERSTATE::ATK_ONEHANDCOMBO;

	player->getPlayerCollisionRc().atkEffFrameX = 0;
	player->getPlayerCollisionRc().atkEffFrameY = 0;
	player->getPlayerCollisionRc().atkPosX = 0;
	player->getPlayerCollisionRc().atkPosY = 0;
	player->getPlayerCollisionRc().atkWidth = 0;
	player->getPlayerCollisionRc().atkHeight = 0;

	// 콤보 비트셋 초기화 + 1단 공격 실행
	_comboStart.reset();
	_comboStart.set(0);
	_comboEnd.reset(0);

	//_timeCount = 0;
	_comboInputMinTime = 0.0f;
	_comboInputMaxTime = 0.0f;
	_playerMotionTime = 0.0f;
}

void TwoHandWeaponCombo::stateUpdate(Player* player)
{

	_comboInputMaxTime += TIMEMANAGER->getElapsedTime();
	_comboInputMinTime += TIMEMANAGER->getElapsedTime();

	if (_comboStart.test(0)) comboOne(player);

	if (_comboInputMinTime > 2.4f && !player->getIsStateCheck().test(2))	
	{
		_comboStart.reset();
		_comboEnd.reset();
		SetPlayerState(player, IdleState::getInstance());
	}

	if (_playerMotionTime >= 0.9f && _playerMotionTime <= 1.0f) player->getPlayerCollisionRc().atkRangeUpdate = true;
	if (_playerMotionTime >= 1.8f) player->getPlayerCollisionRc().atkRangeUpdate = false;

	player->playerAttSetting(_comboStart);
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

void TwoHandWeaponCombo::comboOne(Player * player)
{
	// 이미지 세팅 
	player->getPlayer().image = IMG("p_twoHandCombo_01");


	// 프레임 세팅  
	if (_playerMotionTime <= 1.0f) // 1 combo 1st FrameX
	{
		if (player->getIsStateCheck().test(0)) // L
		{
			_playerMotionTime += TIMEMANAGER->getElapsedTime();
			player->getPlayer().frameX = 0;
		}
		if (!player->getIsStateCheck().test(0)) // R
		{
			_playerMotionTime += TIMEMANAGER->getElapsedTime();
			player->getPlayer().frameX = 1;
		}
	}

	if (_playerMotionTime >= 1.0f && _playerMotionTime <= 2.4f) // 1 combo 2nd FrameX
	{
		_comboInputMaxTime = 0;
		if (player->getIsStateCheck().test(0) && _comboStart.test(0)) // L
		{
			_playerMotionTime += TIMEMANAGER->getElapsedTime();
			player->getPlayer().frameX = 1;
		}
		if (!player->getIsStateCheck().test(0) && _comboStart.test(0)) // R 
		{
			_playerMotionTime += TIMEMANAGER->getElapsedTime();
			player->getPlayer().frameX = 0;
		}
	}
	if (_playerMotionTime >= 2.3f)
	{
		_comboEnd.set(0);
		player->getIsStateCheck().reset(2);
	}
}
