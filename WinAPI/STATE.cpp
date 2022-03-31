#include "Stdafx.h"
#include "STATE.h"
//#include "Player.h"

#ifdef STATEPATTERN


STATE::~STATE()
{
}




void Idle::enterState()
{
	//雌殿拭 級嬢神檎 唖 雌殿原陥 段奄鉢研 背掃艦陥 
	//唖唖税 雌殿拭 魚虞 戚耕走 仙持聖 是廃 index研 段奄鉢
	//_p->setPlayerFrameX(0);
	cout << "企奄 : enterState " << endl;

}

void Idle::updateState()
{
	cout << "企奄 : updateState " << endl;
	count++;
	// 30朝錘闘亜 走蟹檎 煽舌廃 葵精 陥獣 0生稽 段奄鉢 桔艦陥
	// 30朝錘闘(0.5段)走蟹奄 穿 仙脊径馬檎 陥製爪左 雌殿亜 鞠惟 背早柔艦陥
	
	POINT temp;

	// 企奄 -> 号狽徹 刊牽檎 崇送績
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		temp.x = _p->getPlayerPosX() -_p->getPlayerSpeed();
		_p->setPlayerPosX(temp.x);

		_p->setState(PLAYERSTATE::MOVE);
		_p->setPlayerDirection(PLAYERDIRECTION::LEFT);

		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			_p->setPlayerDirection(PLAYERDIRECTION::LEFTUP);
		}
		if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			_p->setPlayerDirection(PLAYERDIRECTION::LEFTDOWN);
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		temp.x = _p->getPlayerPosX() + _p->getPlayerSpeed();
		_p->setPlayerPosX(temp.x);

		_p->setState(PLAYERSTATE::MOVE); 
		_p->setPlayerDirection(PLAYERDIRECTION::RIGHT);

		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			_p->setPlayerDirection(PLAYERDIRECTION::RIGHTUP);
		}
		if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			_p->setPlayerDirection(PLAYERDIRECTION::RIGHTDOWN);
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		temp.y = _p->getPlayerPosY() - _p->getPlayerSpeed();
		_p->setPlayerPosX(temp.y);

		_p->setState(PLAYERSTATE::MOVE);
		_p->setPlayerDirection(PLAYERDIRECTION::UP);

		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			_p->setPlayerDirection(PLAYERDIRECTION::LEFTUP);
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			_p->setPlayerDirection(PLAYERDIRECTION::RIGHTUP);
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		temp.y = _p->getPlayerPosY() + _p->getPlayerSpeed();
		_p->setPlayerPosX(temp.y);

		_p->setState(PLAYERSTATE::MOVE);
		_p->setPlayerDirection(PLAYERDIRECTION::DOWN);

		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			_p->setPlayerDirection(PLAYERDIRECTION::LEFTDOWN);
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			_p->setPlayerDirection(PLAYERDIRECTION::RIGHTDOWN);
		}
	}
	if (KEYMANAGER->isOnceKeyDown('X')) // 析鋼 因維
	{
		_p->setState(PLAYERSTATE::ATT1);
	}
}

void Idle::exitState()
{
	cout << "企奄 : exitState " << endl;

	count = 0; // 雌殿研 纏窒拝凶 企奄乞芝遂 朝錘闘研 段奄鉢馬惟 梅柔艦陥.
}





void Move::enterState()
{
	
}

void Move::updateState()
{
}

void Move::exitState()
{
}









#else
IdleState* IdleState::instance;
MoveState* MoveState::instance;
BeHitState* BeHitState::instance;
DeadState* DeadState::instance;
OneHandWeaponCombo* OneHandWeaponCombo::instance;
TwoHandWeaponCombo* TwoHandWeaponCombo::instance;
SoulCapture* SoulCapture::instance;
SpearStrike* SpearStrike::instance;


// 企奄
IdleState* IdleState::getInstance()
{
	if (instance == nullptr) instance = new IdleState();

	return instance;
}

void IdleState::stateInit(Player* player)
{
	cout << "IdleState::init" << endl;

	if (player->getPlayerWeapon() == WEAPONTYPE::SWORD)
	{
		player->setPlayerImg(IMG("p_idle_oneHand"));
	}
	else if (player->getPlayerWeapon() == WEAPONTYPE::AX)
	{
		player->setPlayerImg(IMG("p_idle_twoHand"));
	}

}

void IdleState::stateUpdate(Player* player)
{
	cout << "IdleState::update" << endl;
	player->setIsFrameImg(false);
	player->setPlayerImg(IMG("p_Idle"));


	if ((KEYMANAGER->isStayKeyDown(VK_LEFT)) || (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		|| (KEYMANAGER->isStayKeyDown(VK_UP)) || (KEYMANAGER->isStayKeyDown(VK_DOWN)))
	{
		cout << "get moveInstance!!!!!" << endl;
		SetPlayerState(player, MoveState::getInstance());
	}

	if (KEYMANAGER->isStayKeyDown('X'))
	{
		cout << "get Att1Instance!!!!!" << endl;
		player->setIsAttacking(true);
		//if 廃謝巷奄檎
		SetPlayerState(player, OneHandWeaponCombo::getInstance());
		// else 砧謝巷奄檎
		//SetPlayerState(player, TwoHandWeaponCombo1::getInstance());

	}

	if (KEYMANAGER->isStayKeyDown('A'))
	{
		SetPlayerState(player, SoulCapture::getInstance());
	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		
		// if 但聖 亜走壱 赤澗走
		SetPlayerState(player, SpearStrike::getInstance());
	}
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		cout << "get 3rd Skill Instance" << endl;
	}

	if (player->getIsHit())
	{
		cout << "杷維雁敗!" << endl;
		SetPlayerState(player, BeHitState::getInstance());
	}

	if (player->getStatus().curHp <= 0)
	{
		SetPlayerState(player, DeadState::getInstance());
	}

}

void IdleState::stateRelease()
{
	cout << "IdleState::release" << endl;
	if (instance)
	{
		delete instance;
		instance = 0;
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

}

void MoveState::stateUpdate(Player * player)
{
	cout << "MoveState::update" << endl;
	player->setIsFrameImg(false);
	player->setPlayerImg(IMG("p_move"));

#pragma region 号狽徹 脊径閤焼 崇送績

	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && !player->getIsRunning())
	{
		//player->setIsLeft(true);
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
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && !player->getIsRunning())
	{
		//player->setIsLeft(false);
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
	if (KEYMANAGER->isStayKeyDown(VK_UP) && !player->getIsRunning())
	{
		player->setPlayerPosY(player->getPlayerPosY() - player->getPlayerSpeed());
		player->setPlayerDirection(PLAYERDIRECTION::UP);


		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			//player->setIsLeft(true);
			player->setPlayerDirection(PLAYERDIRECTION::LEFTUP);
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
		//	player->setIsLeft(false);
			player->setPlayerDirection(PLAYERDIRECTION::RIGHTUP);
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && !player->getIsRunning())
	{
		player->setPlayerPosY(player->getPlayerPosY() + player->getPlayerSpeed());
		player->setPlayerDirection(PLAYERDIRECTION::DOWN);


		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			//player->setIsLeft(true);
			player->setPlayerDirection(PLAYERDIRECTION::LEFTDOWN);
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			//player->setIsLeft(false);
			player->setPlayerDirection(PLAYERDIRECTION::RIGHTDOWN);
		}
	}

	if (KEYOKU(VK_LEFT) || KEYOKU(VK_UP) || KEYOKU(VK_DOWN))
	{
		player->setIsRunning(false);
		SetPlayerState(player, IdleState::getInstance());
	}
	if (KEYOKU(VK_RIGHT))
	{
		player->setIsRunning(false);
		//player->setIsLeft(false);
		SetPlayerState(player, IdleState::getInstance());
	}
	
#pragma endregion

#pragma region 因維/什迭 去

	if (KEYMANAGER->isStayKeyDown('X'))
	{
		cout << "get Att1Instance!!!!!" << endl;
		player->setIsAttacking(true);
		//if 廃謝巷奄檎
		SetPlayerState(player, OneHandWeaponCombo::getInstance());
		// else 砧謝巷奄檎
		//SetPlayerState(player, TwoHandWeaponCombo1::getInstance());

	}

	if (KEYMANAGER->isStayKeyDown('A'))
	{
		SetPlayerState(player, SoulCapture::getInstance());
	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{

		// if 但聖 亜走壱 赤澗走
		SetPlayerState(player, SpearStrike::getInstance());
	}
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		cout << "get 3rd Skill Instance" << endl;
	}

	if (player->getIsHit())
	{
		cout << "限製!" << endl;
		SetPlayerState(player, BeHitState::getInstance());
	}

#pragma endregion 

#pragma region 覗傾績 穣汽戚闘

	PLAYERDIRECTION temp;
	temp = player->getPlayerDirection();

	switch (temp)
	{
		// Y覗傾績幻 室特
	case PLAYERDIRECTION::UP:
		break;
	case PLAYERDIRECTION::DOWN:
		break;
	case PLAYERDIRECTION::LEFT:
		break;
	case PLAYERDIRECTION::RIGHT:
		break;
	case PLAYERDIRECTION::LEFTUP:
		break;
	case PLAYERDIRECTION::RIGHTUP:
		break;
	case PLAYERDIRECTION::LEFTDOWN:
		break;
	case PLAYERDIRECTION::RIGHTDOWN:
		break;

	}



#pragma endregion

}

void MoveState::stateRelease()
{
	cout << "MoveState::release" << endl;

	if (instance)
	{
		delete instance;
		instance = 0;
	}
}



// 杷維
BeHitState* BeHitState::getInstance()
{
	if (instance == nullptr) instance = new BeHitState();
	return instance;
}

void BeHitState::stateInit(Player * player)
{
}

void BeHitState::stateUpdate(Player * player)
{
	cout << "限粧製 ばばばばばば" << endl;
	// 限生檎 析舛獣娃 巷旋
}

void BeHitState::stateRelease()
{
}

DeadState * DeadState::getInstance()
{
	if (instance == nullptr) instance = new DeadState();
	return instance;
}

void DeadState::stateInit(Player * player)
{
}

void DeadState::stateUpdate(Player * player)
{
	// 床君遭 戚耕走 左食層 板 展戚堂稽 戚疑
	cout << "宋製;;;;;;;;;;;;;;;;;;;;;;;" << endl; 

}

void DeadState::stateRelease()
{
}


// 因維
OneHandWeaponCombo* OneHandWeaponCombo::getInstance()
{
	if (instance == nullptr) instance = new OneHandWeaponCombo();
	return instance;
}

void OneHandWeaponCombo::stateInit(Player* player)
{
}

void OneHandWeaponCombo::stateUpdate(Player* player)
{
	cout << "1舘 因維!!" << endl;
	if (KEYMANAGER->isStayKeyDown('X') )
	{
		// 2舘 因維 叔楳

	}
	if (KEYOKU('X') )// && 覗傾績 曽戟 or 朝錘闘 魁蟹檎 企奄乞芝生稽 穿発)
	{
		player->setIsAttacking(false);
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
}

void TwoHandWeaponCombo::stateUpdate(Player * player)
{
}

void TwoHandWeaponCombo::stateRelease()
{
	if (instance)
	{
		delete instance;
		instance = 0;
	}
}


// 什迭 =========================================================
SoulCapture* SoulCapture::getInstance()
{
	if (instance == nullptr) instance = new SoulCapture();
	return instance;
}

void SoulCapture::stateInit(Player * player)
{
}

void SoulCapture::stateUpdate(Player * player)
{
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



#endif // STATEPATTERN
