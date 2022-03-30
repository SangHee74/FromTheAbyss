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
Att1State* Att1State::instance;
Att2State* Att2State::instance;
Att3State* Att3State::instance;
Skill1State* Skill1State::instance;
Skill2State* Skill2State::instance;
Skill3State* Skill3State::instance;




// 企奄
IdleState* IdleState::getInstance()
{
	if (instance == nullptr) instance = new IdleState();

	return instance;
}

void IdleState::stateInit(Player* player)
{
	cout << "IdleState::init" << endl;
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
		SetPlayerState(player, Att1State::getInstance());
	}

	if (KEYMANAGER->isStayKeyDown('A'))
	{
		cout << "get Skill1Instance!!!!!" << endl;
		SetPlayerState(player, Skill1State::getInstance());
	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		cout << "get Skill2Instance!!!!!!!!!!!!!!" << endl;
		SetPlayerState(player, Skill2State::getInstance());
	}
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		cout << "get Skill3Instance!!!!!!!!!!!!!!!!!!" << endl;
		SetPlayerState(player, Skill3State::getInstance());
	}

	if (player->getIsHit())
	{
		cout << "杷維雁敗!" << endl;
		SetPlayerState(player, BeHitState::getInstance());
	}

}

void IdleState::stateRelease(Player* player)
{
	cout << "IdleState::release" << endl;

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
		player->setIsLeft(true);
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
		player->setIsLeft(false);
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
			player->setIsLeft(true);
			player->setPlayerDirection(PLAYERDIRECTION::LEFTUP);
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			player->setIsLeft(false);
			player->setPlayerDirection(PLAYERDIRECTION::RIGHTUP);
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && !player->getIsRunning())
	{
		player->setPlayerPosY(player->getPlayerPosY() + player->getPlayerSpeed());
		player->setPlayerDirection(PLAYERDIRECTION::DOWN);


		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			player->setIsLeft(true);
			player->setPlayerDirection(PLAYERDIRECTION::LEFTDOWN);
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			player->setIsLeft(false);
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
		player->setIsLeft(false);
		SetPlayerState(player, IdleState::getInstance());
	}
	
#pragma endregion

#pragma region 因維/什迭 去

	if (KEYMANAGER->isStayKeyDown('X'))
	{
		cout << "get Att1Instance!!!!!" << endl;
		player->setIsAttacking(true);
		SetPlayerState(player, Att1State::getInstance());
	}

	if (KEYMANAGER->isStayKeyDown('A'))
	{
		cout << "get Skill1Instance!!!!!" << endl;
		SetPlayerState(player, Skill1State::getInstance());
	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		cout << "get Skill2Instance!!!!!!!!!!!!!!" << endl;
		SetPlayerState(player, Skill2State::getInstance());
	}
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		cout << "get Skill3Instance!!!!!!!!!!!!!!!!!!" << endl;
		SetPlayerState(player, Skill3State::getInstance());
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

void MoveState::stateRelease(Player * player)
{
	cout << "MoveState::release" << endl;

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

void BeHitState::stateRelease(Player * player)
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

void DeadState::stateRelease(Player * player)
{
}


// 因維
Att1State* Att1State::getInstance()
{
	if (instance == nullptr) instance = new Att1State();
	return instance;
}

void Att1State::stateInit(Player * player)
{
}

void Att1State::stateUpdate(Player * player)
{
	cout << "1舘 因維!!" << endl;
	if (KEYMANAGER->isStayKeyDown('X') )
	{
		SetPlayerState(player, Att2State::getInstance());
	}
	if (KEYOKU('X') )// && 覗傾績 曽戟 or 朝錘闘 魁蟹檎 企奄乞芝生稽 穿発)
	{
		player->setIsAttacking(false);
		SetPlayerState(player, IdleState::getInstance());
	}

}

void Att1State::stateRelease(Player * player)
{
}


Att2State * Att2State::getInstance()
{
	if (instance == nullptr) instance = new Att2State();
	return instance;
}

void Att2State::stateInit(Player * player)
{
}

void Att2State::stateUpdate(Player * player)
{

	if (KEYMANAGER->isStayKeyDown('X') && player->getPlayerWeapon() != WEAPONTYPE::AX)
	{
		SetPlayerState(player, Att2State::getInstance());
	}
	if (KEYOKU('X'))// && 覗傾績 曽戟 or 朝錘闘 魁蟹檎 企奄乞芝生稽 穿発)
	{
		player->setIsAttacking(false);
		SetPlayerState(player, IdleState::getInstance());
	}

}

void Att2State::stateRelease(Player * player)
{
}

Att3State * Att3State::getInstance()
{
	if (instance == nullptr) instance = new Att3State();
	return instance;
}

void Att3State::stateInit(Player * player)
{
}

void Att3State::stateUpdate(Player * player)
{

	// if( 覗傾績 曽戟 or 朝錘闘 魁蟹檎 企奄乞芝生稽 穿発)
	{
		player->setIsAttacking(false);
		SetPlayerState(player, IdleState::getInstance());
	}
}

void Att3State::stateRelease(Player * player)
{
}

// 什迭 =========================================================
Skill1State * Skill1State::getInstance()
{
	if (instance == nullptr) instance = new Skill1State();
	return instance;
}

void Skill1State::stateInit(Player * player)
{
}

void Skill1State::stateUpdate(Player * player)
{
}

void Skill1State::stateRelease(Player * player)
{
}

Skill2State * Skill2State::getInstance()
{
	if (instance == nullptr) instance = new Skill2State();
	return instance;
}

void Skill2State::stateInit(Player * player)
{
}

void Skill2State::stateUpdate(Player * player)
{
}

void Skill2State::stateRelease(Player * player)
{
}

Skill3State * Skill3State::getInstance()
{
	if (instance == nullptr) instance = new Skill3State();
	return instance;
}

void Skill3State::stateInit(Player * player)
{
}

void Skill3State::stateUpdate(Player * player)
{
}

void Skill3State::stateRelease(Player * player)
{
}

#endif // STATEPATTERN