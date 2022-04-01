#include "Stdafx.h"
#include "StateBase.h"
#include "Player.h"


// 대기, 이동, 피격, 죽음 상태
IdleState* IdleState::instance;
MoveState* MoveState::instance;
//BeHitState* BeHitState::instance;
//DeadState* DeadState::instance;


// 대기
IdleState* IdleState::getInstance()
{
	if (instance == nullptr) instance = new IdleState();

	return instance;
}

void IdleState::stateInit(Player* player)
{
	cout << "IdleState::init" << endl;

	// 이미지 이닛, 프레임 초기화, 에니메이션 초기화 등
	//	player->getIsStateCheck().reset(2);


}

void IdleState::stateUpdate(Player* player)
{
	// timeCount 60 = 1초
	timeCount++;
	if (timeCount % 60 == 0); cout << "IdleState::update" << endl;

	// 공격이 아닐때 이동
	if (!(player->getIsStateCheck().test(2)) &&
		( KEYMANAGER->isStayKeyDown(VK_LEFT)) || (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		|| (KEYMANAGER->isStayKeyDown(VK_UP)) || (KEYMANAGER->isStayKeyDown(VK_DOWN)))
	{
		cout << "get moveInstance" << endl;
		SetPlayerState(player, MoveState::getInstance());
	}

	/*
	// 공격
	if (KEYMANAGER->isStayKeyDown('X'))
	{
		cout << "get AttackInstance!" << endl;

		if ((player->getPlayerWeapon() == WEAPONTYPE::SWORD) ||
			(player->getPlayerWeapon() == WEAPONTYPE::AX))
		{
			SetPlayerState(player, OneHandWeaponCombo::getInstance());
		}
		if (player->getPlayerWeapon() == WEAPONTYPE::SPEAR)
		{
			//SetPlayerState(player, TwoHandWeaponCombo::getInstance());
		}
	}

	// 스킬
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		//SetPlayerState(player, SoulCapture::getInstance());
	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		// 창을 장착하고 있으면 스킬로
		if (player->getPlayerWeapon() == WEAPONTYPE::SPEAR)
		{
			//SetPlayerState(player, SpearStrike::getInstance());
		}
	}
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		cout << "get 3rd Skill Instance" << endl;
	}

	// 피격
	if (player->getIsStateCheck().test(3))
	{
		cout << "피격당함!" << endl;
		SetPlayerState(player, BeHitState::getInstance());
	}

	// 죽음
	if (player->getStatus().curHp <= 0)
	{
		SetPlayerState(player, DeadState::getInstance());
	}
	*/
}

void IdleState::stateRelease()
{
	cout << "IdleState::release" << endl;
	//if (instance )
	//{
	//	delete instance;
	//	instance = 0;	
	//}
}

void IdleState::stateRender(Player* player)
{

	// 플레이어가 무기 아래에 렌더
	if (player->getPState().test(5))
	{



		//player->frameRender(getMemDC(), left, top, _frameX, _frameY);

	// 달리기, 피격, 죽음 상태
	//if (_isStateCheck.test(1) || _isStateCheck.test(3) || !_isStateCheck.test(4))
	//{
	//}
	//else _weaponimage->frameRender(getMemDC(), weaponLeft, weaponTop, 1, _playerWeapon.frameY);
	}
}

// 이동
MoveState* MoveState::getInstance()
{
	if (instance == nullptr) instance = new MoveState();
	return instance;
}

void MoveState::stateInit(Player * player)
{
	cout << "MoveState::init" << endl;
	player->getIsStateCheck().set(1);




}

void MoveState::stateUpdate(Player * player)
{
	timeCount++;
	if (timeCount % 120 == 0); cout << "MoveState::update" << endl;


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
			player->getIsStateCheck().reset(0);
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
			player->getIsStateCheck().reset(0);
			player->setPlayerDirection(PLAYERDIRECTION::RIGHTDOWN);
		}
	}

	//방향키 입력 종료
	if (player->getIsStateCheck().test(1))
	{
		// 대기상태로 돌아가는 조건은 어케해야대나 ..
		// x프레임이 모두 돌고 나면 달리기 off ,
		// 달리기 오프면 대기로. 
		SetPlayerState(player, IdleState::getInstance());
	}

	/*
	// 공격
	if (KEYMANAGER->isStayKeyDown('X'))
	{
		cout << "get AttackInstance!" << endl;

		if ((player->getPlayerWeapon() == WEAPONTYPE::SWORD) ||
			(player->getPlayerWeapon() == WEAPONTYPE::AX))
		{
			SetPlayerState(player, OneHandWeaponCombo::getInstance());
		}
		if (player->getPlayerWeapon() == WEAPONTYPE::SPEAR)
		{
		//	SetPlayerState(player, TwoHandWeaponCombo::getInstance());
		}
	}

	// 스킬
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		//SetPlayerState(player, SoulCapture::getInstance());
	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		// 창을 장착하고 있으면 스킬로
		if (player->getPlayerWeapon() == WEAPONTYPE::SPEAR)
		{
		//	SetPlayerState(player, SpearStrike::getInstance());
		}
	}
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		cout << "get 3rd Skill Instance" << endl;
	}

	// 피격
	if (player->getIsStateCheck().test(3))
	{
		cout << "피격당함!" << endl;
		SetPlayerState(player, BeHitState::getInstance());
	}

	// 죽음
	if (player->getStatus().curHp <= 0)
	{
		SetPlayerState(player, DeadState::getInstance());
	}

	*/

	if (timeCount % 10 == 0)
	{
		// 플레이어 왼쪽
		if (player->getIsStateCheck().test(0))
		{
			player->setPlayerFrameX(player->getPlayerFrameX() + 1);
			if (player->getPlayerFrameX() >= 3)
			{
				player->setPlayerFrameX(0);

				if (KEYOKU(VK_RIGHT) || KEYOKU(VK_LEFT) || KEYOKU(VK_UP) || KEYOKU(VK_DOWN))
				{
					// 프레임이 끝까지 다 돌았을때 키를 떼면 달리기 종료
					player->getIsStateCheck().reset(1);

				}
			}
		}
		else
		{
			player->setPlayerFrameX(player->getPlayerFrameX() - 1);
			if (player->getPlayerFrameX() < 0)
			{
				player->setPlayerFrameX(3);

				if (KEYOKU(VK_RIGHT) || KEYOKU(VK_LEFT) || KEYOKU(VK_UP) || KEYOKU(VK_DOWN))
				{
					// 프레임이 끝까지 다 돌았을때 키를 떼면 달리기 종료
					player->getIsStateCheck().reset(1);

				}
			}
		}
	}


}

void MoveState::stateRelease()
{
	cout << "MoveState::release" << endl;

	//if (instance)
	//{
	//	delete instance;
	//	instance = 0;
	//}
}

void MoveState::stateRender(Player* player)
{
}


#if 0
// 피격
BeHitState* BeHitState::getInstance()
{
	if (instance == nullptr) instance = new BeHitState();
	return instance;
}

void BeHitState::stateInit(Player * player)
{
	if (timeCount % 180 == 0) cout << "BeHitState::Init" << endl;
	player->getIsStateCheck().set(3);


}

void BeHitState::stateUpdate(Player * player)
{
	timeCount++;
	if (timeCount % 120 == 0) cout << "맞앗음 ㅠㅠㅠㅠㅠㅠ" << endl;
	// 맞으면 일정시간 무적

	// 왼쪽에서 맞으면 오른쪽으로 약간 이동 
	if (player->getIsStateCheck().test(0))
	{
		player->setPlayerPosX(player->getPlayerPosX() + (player->getPlayerSpeed()*0.5));
	}
	else player->setPlayerPosX(player->getPlayerPosX() - (player->getPlayerSpeed()*0.5));
}

void BeHitState::stateRelease()
{
	cout << "BeHitState::release" << endl;

	if (instance)
	{
		delete instance;
		instance = 0;
	}
}

DeadState * DeadState::getInstance()
{
	if (instance == nullptr) instance = new DeadState();
	return instance;
}

void DeadState::stateInit(Player * player)
{

	cout << "DeadState::init" << endl;
	player->getIsStateCheck().reset(4);

	player->setPlayerImg(IMG("p_down"));


}

void DeadState::stateUpdate(Player * player)
{
	// 쓰러진 이미지 보여준 후 타이틀로 이동
	cout << "죽음;;;;;;;;;;;;;;;;;;;;;;;" << endl;

}

void DeadState::stateRelease()
{
	cout << "DeadState::release" << endl;

	if (instance)
	{
		delete instance;
		instance = 0;
	}
}



#endif
