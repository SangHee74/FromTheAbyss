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
	//	player->getIsStateCheck().reset(2);


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

	// 巴傾戚嬢亜 巷奄 焼掘拭 兄希
	if (player->getPState().test(5))
	{



		//player->frameRender(getMemDC(), left, top, _frameX, _frameY);

	// 含軒奄, 杷維, 宋製 雌殿
	//if (_isStateCheck.test(1) || _isStateCheck.test(3) || !_isStateCheck.test(4))
	//{
	//}
	//else _weaponimage->frameRender(getMemDC(), weaponLeft, weaponTop, 1, _playerWeapon.frameY);
	}
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
	player->getIsStateCheck().set(1);




}

void MoveState::stateUpdate(Player * player)
{
	timeCount++;
	if (timeCount % 120 == 0); cout << "MoveState::update" << endl;


	// 疎
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
	// 酔
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
	// 是
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
	// 焼掘
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

	//号狽徹 脊径 曽戟
	if (player->getIsStateCheck().test(1))
	{
		// 企奄雌殿稽 宜焼亜澗 繕闇精 嬢追背醤企蟹 ..
		// x覗傾績戚 乞砧 宜壱 蟹檎 含軒奄 off ,
		// 含軒奄 神覗檎 企奄稽. 
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

	if (timeCount % 10 == 0)
	{
		// 巴傾戚嬢 図楕
		if (player->getIsStateCheck().test(0))
		{
			player->setPlayerFrameX(player->getPlayerFrameX() + 1);
			if (player->getPlayerFrameX() >= 3)
			{
				player->setPlayerFrameX(0);

				if (KEYOKU(VK_RIGHT) || KEYOKU(VK_LEFT) || KEYOKU(VK_UP) || KEYOKU(VK_DOWN))
				{
					// 覗傾績戚 魁猿走 陥 宜紹聖凶 徹研 脅檎 含軒奄 曽戟
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
					// 覗傾績戚 魁猿走 陥 宜紹聖凶 徹研 脅檎 含軒奄 曽戟
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
