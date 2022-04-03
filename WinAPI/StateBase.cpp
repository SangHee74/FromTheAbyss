#include "Stdafx.h"
#include "StateBase.h"
#include "Player.h"


// 企奄, 戚疑, 杷維, 宋製 雌殿
IdleState* IdleState::instance;
MoveState* MoveState::instance;
//BeHitState* BeHitState::instance;
//DeadState* DeadState::instance;


// 企奄
IdleState* IdleState::getInstance()
{
	if (instance == nullptr) instance = new IdleState();

	return instance;
}

void IdleState::stateInit(Player* player)
{
	cout << "IdleState::init" << endl;

	// 戚耕走 戚間, 覗傾績 段奄鉢, 拭艦五戚芝 段奄鉢 去
	// 企奄 : 戚疑, 因維, 杷維 段奄鉢
	player->getIsStateCheck().reset(1);
	player->getIsStateCheck().reset(2);
	player->getIsStateCheck().reset(3);

	player->setState(PLAYERSTATE::IDLE);

}

void IdleState::stateUpdate(Player* player)
{
	// timeCount 60 = 1段
	timeCount++;
	if (timeCount % 60 == 0); cout << "IdleState::update" << endl;

	// 因維戚 焼諌凶 戚疑
	if (!(player->getIsStateCheck().test(2)) &&
		( KEYMANAGER->isStayKeyDown(VK_LEFT)) || (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		|| (KEYMANAGER->isStayKeyDown(VK_UP)) || (KEYMANAGER->isStayKeyDown(VK_DOWN)))
	{
		cout << "get moveInstance" << endl;
		SetPlayerState(player, MoveState::getInstance());
	}

	/*
	// 因維
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

	// 什迭
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		//SetPlayerState(player, SoulCapture::getInstance());
	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		// 但聖 舌鐸馬壱 赤生檎 什迭稽
		if (player->getPlayerWeapon() == WEAPONTYPE::SPEAR)
		{
			//SetPlayerState(player, SpearStrike::getInstance());
		}
	}
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		cout << "get 3rd Skill Instance" << endl;
	}

	// 杷維
	if (player->getIsStateCheck().test(3))
	{
		cout << "杷維雁敗!" << endl;
		SetPlayerState(player, BeHitState::getInstance());
	}

	// 宋製
	if (player->getStatus().curHp <= 0)
	{
		SetPlayerState(player, DeadState::getInstance());
	}
	*/

	
	PLAYERDIRECTION _tempDirection;
	_tempDirection = player->getDirection();

	// 企奄掻 兄希 疎妊 穣汽戚闘 
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
	
	// 巷奄痕発 砺什闘
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

	// 戚耕走 哀焼晦奄
	if (player->getPlayerWeapon().type == WEAPONTYPE::SWORD) player->getPlayer().image = IMG("p_idle_oneHand");
	else if (player->getPlayerWeapon().type == WEAPONTYPE::AX) player->getPlayer().image = IMG("p_idle_oneHand");
	else if (player->getPlayerWeapon().type == WEAPONTYPE::SPEAR) player->getPlayer().image = IMG("p_idle_twoHand");
	player->getPlayer().image->setFrameX(0); // 戚板 焼戚奴角獄 亜閃神奄

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

// 戚疑
MoveState* MoveState::getInstance()
{
	if (instance == nullptr) instance = new MoveState();
	return instance;
}

void MoveState::stateInit(Player * player)
{
	cout << "MoveState::init" << endl;

	// 戚疑 : 因維, 杷維 段奄鉢

	player->getIsStateCheck().reset(2);
	player->getIsStateCheck().reset(3);
	player->getIsStateCheck().set(1);

	player->setState(PLAYERSTATE::MOVE);

}

// !!!!!!!!!!!!!!!! 巷崎 図楕戚疑 覗傾績 穣汽戚闘 呪舛!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void MoveState::stateUpdate(Player * player)
{
	timeCount++;
	if (timeCount % 60 == 0); cout << "MoveState::update" << endl;

	
	// 雌
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
	// 馬
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
	// 疎
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
	// 酔
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
	// 因維
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

	// 什迭
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		//SetPlayerState(player, SoulCapture::getInstance());
	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		// 但聖 舌鐸馬壱 赤生檎 什迭稽
		if (player->getPlayerWeapon() == WEAPONTYPE::SPEAR)
		{
		//	SetPlayerState(player, SpearStrike::getInstance());
		}
	}
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		cout << "get 3rd Skill Instance" << endl;
	}

	// 杷維
	if (player->getIsStateCheck().test(3))
	{
		cout << "杷維雁敗!" << endl;
		SetPlayerState(player, BeHitState::getInstance());
	}

	// 宋製
	if (player->getStatus().curHp <= 0)
	{
		SetPlayerState(player, DeadState::getInstance());
	}

	*/

	if (timeCount % 30 == 0)
	{
		// 巴傾戚嬢 図楕
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
// 杷維
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
	if (timeCount % 120 == 0) cout << "限粧製 ばばばばばば" << endl;
	// 限生檎 析舛獣娃 巷旋

	// 図楕拭辞 限生檎 神献楕生稽 鉦娃 戚疑 
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
	// 床君遭 戚耕走 左食層 板 展戚堂稽 戚疑
	cout << "宋製;;;;;;;;;;;;;;;;;;;;;;;" << endl;

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
