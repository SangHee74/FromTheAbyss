#include "Stdafx.h"
#include "StateBase.h"
#include "StateAttack.h"
#include "Player.h"

// 企奄, 戚疑, 杷維, 宋製 雌殿
IdleState* IdleState::instance;
MoveState* MoveState::instance;
HitState* HitState::instance;
DeadState* DeadState::instance;

// 企奄
IdleState* IdleState::getInstance()
{
	if (instance == nullptr) instance = new IdleState();
	return instance;
}

void IdleState::stateInit(Player* player)
{
	// 戚耕走 戚間, 覗傾績 段奄鉢, 拭艦五戚芝 段奄鉢 去
	// 企奄 : 戚疑, 因維, 杷維 段奄鉢
	player->getIsStateCheck().reset(1);
	player->getIsStateCheck().reset(2);
	player->getIsStateCheck().reset(3);

	player->setState(PLAYERSTATE::IDLE);

	// 巴傾戚嬢 巷奄展脊(image), 号狽(frameX), 巷奄腰硲(frameY)+ 巷奄疎妊 室特
	player->inStageWeaponSetting();

}

void IdleState::stateUpdate(Player* player)
{
#pragma region player

	// 戚疑
	if (!(player->getIsStateCheck().test(2)) &&
		( KEYMANAGER->isStayKeyDown(VK_LEFT)) || (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		|| (KEYMANAGER->isStayKeyDown(VK_UP)) || (KEYMANAGER->isStayKeyDown(VK_DOWN)))
	{
		SetPlayerState(player, MoveState::getInstance());
	}

	// 因維
	if (KEYMANAGER->isStayKeyDown('X'))
	{
		if ((player->getPlayerWeapon().type == WEAPONTYPE::SWORD) ||
			(player->getPlayerWeapon().type == WEAPONTYPE::AX))
		{
			SetPlayerState(player, OneHandWeaponCombo::getInstance());
		}
		if (player->getPlayerWeapon().type == WEAPONTYPE::SPEAR)
		{
			SetPlayerState(player, TwoHandWeaponCombo::getInstance());
		}
	}

	/*
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
	*/

	// 杷維
	if (player->getIsStateCheck().test(3))
	{
		cout << "杷維雁敗!" << endl;
		SetPlayerState(player, HitState::getInstance());
	}

	// 宋製
	if (player->getPlayerStatus().curHp <= 0)
	{
		SetPlayerState(player, DeadState::getInstance());
	}


	
#pragma endregion

#pragma region weapon

	// 巷奄痕発 砺什闘
	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		player->getPlayerWeapon().type = WEAPONTYPE::SWORD;
		player->inStageWeaponSetting();

	}
	if (KEYMANAGER->isOnceKeyDown('2'))
	{
		player->getPlayerWeapon().type = WEAPONTYPE::AX;
		player->inStageWeaponSetting();

	}
	if (KEYMANAGER->isOnceKeyDown('3'))
	{
		player->getPlayerWeapon().type = WEAPONTYPE::SPEAR;
		player->inStageWeaponSetting();

	}
	if (KEYMANAGER->isOnceKeyDown('4'))
	{
	}

#pragma endregion

	player->getPlayer().frameX = 0;
}

void IdleState::stateRelease()
{
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
	// 戚疑 : 因維, 杷維 段奄鉢
	player->getIsStateCheck().reset(2);
	player->getIsStateCheck().reset(3);
	player->getIsStateCheck().set(1);

	player->setState(PLAYERSTATE::MOVE);

	timeCount = 0;
}

void MoveState::stateUpdate(Player* player)
{
	timeCount++;
	player->getPlayer().image = IMG("p_move");
	
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
		SetPlayerState(player, IdleState::getInstance());
	}


	
	// 因維
	if (KEYMANAGER->isStayKeyDown('X'))
	{
		cout << "get AttackInstance!" << endl;

		if ((player->getPlayerWeapon().type == WEAPONTYPE::SWORD) ||
			(player->getPlayerWeapon().type == WEAPONTYPE::AX))
		{
			SetPlayerState(player, OneHandWeaponCombo::getInstance());
		}
		if (player->getPlayerWeapon().type == WEAPONTYPE::SPEAR)
		{
			SetPlayerState(player, TwoHandWeaponCombo::getInstance());
		}
	}
	/*
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

	*/

	// 杷維
	if (player->getIsStateCheck().test(3))
	{
		cout << "杷維雁敗!" << endl;
		SetPlayerState(player, HitState::getInstance());
	}

	// 宋製
	if (player->getPlayerStatus().curHp <= 0)
	{
		SetPlayerState(player, DeadState::getInstance());
	}


	if (timeCount % 10 == 0)
	{
		// 巴傾戚嬢 図楕
		if (player->getIsStateCheck().test(0))
		{
			frameIndexX++;
			if (frameIndexX > 3) frameIndexX = 0;
		}
		else
		{
			frameIndexX--;
			if (frameIndexX < 0) frameIndexX = 3;
		}
		

		// 段奄鉢 : 1段
		if (timeCount==60) timeCount = 0;
	}

	player->getPlayer().frameX = frameIndexX;
	player->getPlayerWeapon().image = IMG("weapon_none");
}

void MoveState::stateRelease()
{
	//if (instance)
	//{
	//	delete instance;
	//	instance = 0;
	//}
}

void MoveState::stateRender(Player* player)
{
}



// 杷維
HitState* HitState::getInstance()
{
	if (instance == nullptr) instance = new HitState();
	return instance;
}

void HitState::stateInit(Player* player)
{
	player->getIsStateCheck().set(3);
	player->setState(PLAYERSTATE::HIT);


}

void HitState::stateUpdate(Player* player)
{
	timeCount++;
	player->getPlayer().image = IMG("p_hit");
	player->getPlayerWeapon().image = IMG("weapon_none");

	if (timeCount % 60 == 0) cout << "限粧製 ばばばばばば" << endl;
	// 限生檎 析舛獣娃 巷旋

	// 図楕拭辞 限生檎 神献楕生稽 鉦娃 戚疑 
	if (player->getIsStateCheck().test(0))
	{
		player->getPlayer().movePosX - (player->getPlayer().speed*0.5);
	}
	else if (!player->getIsStateCheck().test(0))
	{
		player->getPlayer().movePosX + (player->getPlayer().speed*0.5);
	}

	player->getPlayer().frameX = 0;
	
	// 2段
	if (timeCount % 120 == 0)
	{
		SetPlayerState(player, IdleState::getInstance());
	}


}

void HitState::stateRelease()
{
	if (instance)
	{
		delete instance;
		instance = 0;
	}
}

void HitState::stateRender(Player* player)
{
}

DeadState* DeadState::getInstance()
{
	if (instance == nullptr) instance = new DeadState();
	return instance;
}

void DeadState::stateInit(Player * player)
{

	player->setState(PLAYERSTATE::DEAD);
}

void DeadState::stateUpdate(Player* player)
{
	// 床君遭 戚耕走 左食層 板 展戚堂稽 戚疑
	timeCount++;
	player->getPlayer().image = IMG("p_down");
	player->getPlayerWeapon().image = IMG("weapon_none");

	player->getPlayer().frameX = 0;

	// 3段 
	if (timeCount % 180 == 0)
	{
		player->getIsStateCheck().reset(4);
	}

}

void DeadState::stateRelease()
{
	cout << "DeadState::release" << endl;

	//if (instance)
	//{
	//	delete instance;
	//	instance = 0;
	//}
}

void DeadState::stateRender(Player* player)
{
}

#if 0

#endif
