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
	// 대기 : 이동, 공격, 피격 초기화
	player->getIsStateCheck().reset(1);
	player->getIsStateCheck().reset(2);
	player->getIsStateCheck().reset(3);

	player->setState(PLAYERSTATE::IDLE);

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

	
	PLAYERDIRECTION _tempDirection;
	_tempDirection = player->getDirection();

	// 대기중 렌더 좌표 업데이트 
	switch (_tempDirection)
	{
	case PLAYERDIRECTION::UP:
		player->getPlayerWeapon().drawPosX = player->getPlayerWeapon().movePosX - 23;
		player->getPlayerWeapon().drawPosY = player->getPlayerWeapon().movePosY - 27;
		break;
	case PLAYERDIRECTION::DOWN:
		player->getPlayerWeapon().drawPosX = player->getPlayerWeapon().movePosX - 23;
		player->getPlayerWeapon().drawPosY = player->getPlayerWeapon().movePosY - 27;
		break;
	case PLAYERDIRECTION::LEFT:
		player->getPlayerWeapon().drawPosX = player->getPlayerWeapon().movePosX - 23;
		player->getPlayerWeapon().drawPosY = player->getPlayerWeapon().movePosY - 27;
		break;
	case PLAYERDIRECTION::RIGHT:
		player->getPlayerWeapon().drawPosX = player->getPlayerWeapon().movePosX - 23;
		player->getPlayerWeapon().drawPosY = player->getPlayerWeapon().movePosY - 27;
		break;
	case PLAYERDIRECTION::LEFTUP:
		player->getPlayerWeapon().drawPosX = player->getPlayerWeapon().movePosX - 23;
		player->getPlayerWeapon().drawPosY = player->getPlayerWeapon().movePosY - 27;
		break;
	case PLAYERDIRECTION::RIGHTUP:
		player->getPlayerWeapon().drawPosX = player->getPlayerWeapon().movePosX - 23;
		player->getPlayerWeapon().drawPosY = player->getPlayerWeapon().movePosY - 27;
		break;
	case PLAYERDIRECTION::LEFTDOWN:
		player->getPlayerWeapon().drawPosX = player->getPlayerWeapon().movePosX - 23;
		player->getPlayerWeapon().drawPosY = player->getPlayerWeapon().movePosY - 27;
		break;
	case PLAYERDIRECTION::RIGHTDOWN:
		player->getPlayerWeapon().drawPosX = player->getPlayerWeapon().movePosX - 23;
		player->getPlayerWeapon().drawPosY = player->getPlayerWeapon().movePosY - 27;
		break;
	}
	
	// 무기변환 테스트
	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		player->getPlayerWeapon().type = WEAPONTYPE::SWORD;
	}
	if (KEYMANAGER->isOnceKeyDown('2'))
	{
		player->getPlayerWeapon().type = WEAPONTYPE::AX;
	}
	if (KEYMANAGER->isOnceKeyDown('3'))
	{
		player->getPlayerWeapon().type = WEAPONTYPE::SPEAR;
	}

	// 이미지 갈아끼기
	if (player->getPlayerWeapon().type == WEAPONTYPE::SWORD) player->getPlayer().image = IMG("p_idle_oneHand");
	else if (player->getPlayerWeapon().type == WEAPONTYPE::AX) player->getPlayer().image = IMG("p_idle_oneHand");
	else if (player->getPlayerWeapon().type == WEAPONTYPE::SPEAR) player->getPlayer().image = IMG("p_idle_twoHand");
	player->getPlayer().image->setFrameX(0); // 이후 아이템넘버 가져오기

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

	// 이동 : 공격, 피격 초기화

	player->getIsStateCheck().reset(2);
	player->getIsStateCheck().reset(3);
	player->getIsStateCheck().set(1);

	player->setState(PLAYERSTATE::MOVE);

}

// !!!!!!!!!!!!!!!! 무브 왼쪽이동 프레임 업데이트 수정!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void MoveState::stateUpdate(Player * player)
{
	timeCount++;
	if (timeCount % 60 == 0); cout << "MoveState::update" << endl;

	
	// 상
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		player->getPlayer().movePosY -= player->getPlayer().speed;
		player->getPlayerWeapon().movePosY = player->getPlayer().movePosY;
		
		player->setDirection(PLAYERDIRECTION::UP);

		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			player->getIsStateCheck().set(0);
			player->setDirection(PLAYERDIRECTION::LEFTUP);
		}
		if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
		{
			player->getIsStateCheck().set(0);
			player->setDirection(PLAYERDIRECTION::LEFTUP);
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			player->getIsStateCheck().reset(0);
			player->setDirection(PLAYERDIRECTION::RIGHTUP);
		}
		if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
		{
			player->getIsStateCheck().reset(0);
			player->setDirection(PLAYERDIRECTION::RIGHTUP);
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_UP))
	{
		cout << "get idleInstance" << endl;
		SetPlayerState(player, IdleState::getInstance());
	}
	// 하
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		player->getPlayer().movePosY += player->getPlayer().speed;
		player->getPlayerWeapon().movePosY = player->getPlayer().movePosY;
		player->setDirection(PLAYERDIRECTION::DOWN);


		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			player->getIsStateCheck().set(0);
			player->setDirection(PLAYERDIRECTION::LEFTDOWN);
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			player->getIsStateCheck().reset(0);
			player->setDirection(PLAYERDIRECTION::RIGHTDOWN);
		}
		if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
		{
			player->getIsStateCheck().set(0);
			player->setDirection(PLAYERDIRECTION::LEFTDOWN);
		}
		if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
		{
			player->getIsStateCheck().reset(0);
			player->setDirection(PLAYERDIRECTION::RIGHTDOWN);
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
	{
		cout << "get idleInstance" << endl;
		SetPlayerState(player, IdleState::getInstance());
	}
	// 좌
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		player->getIsStateCheck().set(0);
		player->getPlayer().movePosX -= player->getPlayer().speed;
		player->getPlayerWeapon().movePosX = player->getPlayer().movePosX;

		player->setDirection(PLAYERDIRECTION::LEFT);

		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			player->setDirection(PLAYERDIRECTION::LEFTUP);
		}
		if (KEYMANAGER->isOnceKeyUp(VK_UP))
		{
			player->setDirection(PLAYERDIRECTION::LEFTUP);
		}
		if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			player->setDirection(PLAYERDIRECTION::LEFTDOWN);
		}
		if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
		{
			player->setDirection(PLAYERDIRECTION::LEFTDOWN);
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		cout << "get idleInstance" << endl;
		SetPlayerState(player, IdleState::getInstance());
	}
	// 우
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		player->getIsStateCheck().reset(0);
		player->getPlayer().movePosX += player->getPlayer().speed;
		player->getPlayerWeapon().movePosX = player->getPlayer().movePosX;
		player->setDirection(PLAYERDIRECTION::RIGHT);

		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			player->setDirection(PLAYERDIRECTION::RIGHTUP);
		}
		if (KEYMANAGER->isOnceKeyUp(VK_UP))
		{
			player->setDirection(PLAYERDIRECTION::RIGHTUP);
		}
		if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			player->setDirection(PLAYERDIRECTION::RIGHTDOWN);
		}
		if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
		{
			player->setDirection(PLAYERDIRECTION::RIGHTDOWN);
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		cout << "get idleInstance" << endl;
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

	if (timeCount % 30 == 0)
	{
		// 플레이어 왼쪽
		if (player->getIsStateCheck().test(0))
		{
			player->getPlayer().frameX += 1;
			if ( player->getPlayer().frameX >= 3)
			{
				player->getPlayer().frameX = 0;
			}
		}
		else
		{
			player->getPlayer().frameX -= 1;
			if (player->getPlayer().frameX < 0)
			{
				player->getPlayer().frameX = 3;
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
