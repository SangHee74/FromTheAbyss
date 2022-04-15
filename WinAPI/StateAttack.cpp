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

	// 방향별 무기 프레임 지정(comboOne 1,2 /  comboTwo 1,2 / comboThree 1,2 ) : 총 6개
	// 스위치로 플레이어 방향 받아서 지정.

}

void OneHandWeaponCombo::stateUpdate(Player* player)
{
	// 60카운트(1초)지나기 전 재입력하면 다음콤보
	// 콤보에서 시간초 초기화.

	_comboInputMaxTime += TIMEMANAGER->getElapsedTime();
	_comboInputMinTime += TIMEMANAGER->getElapsedTime();
	
	if (_comboStart.test(0)) comboOne(player);
	if (KEYSKD('x') && _comboInputMinTime > 0.5f && _comboEnd.test(0) )
	{
		player->getIsStateCheck().set(2);
		_comboInputMinTime = 0;
		_comboInputMaxTime = 0;
		cout << "한손공격 - 2단 콤보" << endl;
		_comboStart.set(1);
	}
	if (KEYSKD('x') && _comboInputMinTime > 1.0f && _comboEnd.test(1) )
	{
		player->getIsStateCheck().set(2);
		_comboInputMinTime = 0;
		_comboInputMaxTime = 0;
		cout << "한손공격 - 3단 콤보" << endl;
		_comboStart.set(2);
	}
	//cout << "--------------------------------------------------" << endl;
//	cout << "콤보 종료까지 걸리는 시간 :" << _comboInputMinTime << endl;
	//프레임 종료 or 카운트 끝나면 대기모션으로 전환)
	if ( _comboInputMinTime > 0.7f					 // 키입력 시간 초과
		 && !player->getIsStateCheck().test(2)    )  // 공격상태 아님
	{
		_comboStart.reset();
		_comboEnd.reset();

		cout << " 키 입력 시간초과! 대기상태로 전환합니다." << endl;
		SetPlayerState(player, IdleState::getInstance());

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
	// 좌우 비트셋
	if (player->getDirection() == PLAYERDIRECTION::RIGHT
		|| player->getDirection() == PLAYERDIRECTION::RIGHTUP
		|| player->getDirection() == PLAYERDIRECTION::RIGHTDOWN)
	{
	//	cout << "오른쪽임! 프레임을 1부터 시작, -1" << endl;
	}
	else
	{
		player->getIsStateCheck().set(0);
	//	cout << "왼쪽임!!!!! 프레임을 0부터 시작, +1" << endl;
	}


	// 이미지 세팅 
	player->getPlayer().image = IMG("p_oneHandCombo_01");
	player->getPlayerCollisionRc().atkEffectImg = IMG("eff_sword");

	
	// 프레임 세팅  
	// 1콤보 첫번째 프레임 
	if (_playerMotionTime <= 3.0f)
	{
		if (player->getIsStateCheck().test(0)) // L
		{
		//	cout << "player FrameX 1-1 , Left " << endl;
			_playerMotionTime++; // 프레임이 있는 경우에만 증가
			player->getPlayer().frameX = 0;
			player->getPlayerCollisionRc().atkEffFrameX = 1;
			player->getPlayerCollisionRc().atkEffFrameY = 1;
		}
		if (!player->getIsStateCheck().test(0)) // R
		{
		//	cout << "player FrameX 1-1 , Right " << endl;
			_playerMotionTime++;
			player->getPlayer().frameX = 1;						// 캐릭터 프레임
			player->getPlayerCollisionRc().atkEffFrameX = 0;	// 이펙트 프레임 
			player->getPlayerCollisionRc().atkEffFrameY = 0;

		}
		// 콤보-프레임 별 무기 프레임 업데이트 + 타격범위 업데이트
		player->playerAttSetting(_comboStart);						// 공격범위 업데이트 		
	}


	// 1콤보 두번째 프레임
	if (_playerMotionTime >= 3.1f && _playerMotionTime <= 7.4f)
	{
		_comboInputMaxTime = 0;
		// 왼쪽이고, 콤보 1단 중임
		if (player->getIsStateCheck().test(0) && _comboStart.test(0)) // L
		{
		//	cout << "player FrameX 1-2 , Left " << endl;
			_playerMotionTime++;
			player->getPlayer().frameX += 1;
			player->getPlayerCollisionRc().atkEffFrameX += 1;
			if (player->getPlayer().frameX == player->getPlayer().image->getMaxFrameX())
			{
				player->getPlayer().frameX = player->getPlayer().image->getMaxFrameX();
				//_comboInputMaxTime++;
			}
		}
		// 오른쪽이고, 콤보 1단 중임
		if (!player->getIsStateCheck().test(0) && _comboStart.test(0)) // R 
		{
		//	cout << "player FrameX 1-2 , Right " << endl;
			_playerMotionTime++;
			player->getPlayer().frameX -= 1;
			player->getPlayerCollisionRc().atkEffFrameX -= 1;
			if (player->getPlayer().frameX < 0)
			{
				player->getPlayer().frameX = 0;
				//_comboInputMaxTime++;
			}
		}
		player->playerAttSetting(_comboStart);
	}


	if (_playerMotionTime > 7.5f)			// 콤보 1단 모션이 모두 끝나면
	{
		_comboEnd.set(0);				    // 1단콤보 종료됨
		player->getIsStateCheck().reset(2); // 공격상태 꺼짐
	//	cout << "1단 콤보 종료됨 " << endl;


	}


}

void OneHandWeaponCombo::comboTwo(Player* player)
{
	player->getPlayer().image = IMG("p_oneHandCombo_02");

	player->getIsStateCheck().set(2);

	cout << "한손무기 2단 공격 함수" << endl;


}

void OneHandWeaponCombo::comboThree(Player* player)
{
	player->getPlayer().image = IMG("p_oneHandCombo_03");

	player->getIsStateCheck().set(2);

	cout << "한손무기 3단 공격 함수" << endl;


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