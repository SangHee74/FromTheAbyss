#include "Stdafx.h"
#include "STATE.h"
//#include "Player.h"

#ifdef STATEPATTERN


STATE::~STATE()
{
}




void Idle::enterState()
{
	//���¿� ������ �� ���¸��� �ʱ�ȭ�� ���ݴϴ� 
	//������ ���¿� ���� �̹��� ����� ���� index�� �ʱ�ȭ
	//_p->setPlayerFrameX(0);
	cout << "��� : enterState " << endl;

}

void Idle::updateState()
{
	cout << "��� : updateState " << endl;
	count++;
	// 30ī��Ʈ�� ������ ������ ���� �ٽ� 0���� �ʱ�ȭ �˴ϴ�
	// 30ī��Ʈ(0.5��)������ �� ���Է��ϸ� �����޺� ���°� �ǰ� ������ϴ�
	
	POINT temp;

	// ��� -> ����Ű ������ ������
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
	if (KEYMANAGER->isOnceKeyDown('X')) // �Ϲ� ����
	{
		_p->setState(PLAYERSTATE::ATT1);
	}
}

void Idle::exitState()
{
	cout << "��� : exitState " << endl;

	count = 0; // ���¸� Ż���Ҷ� ����ǿ� ī��Ʈ�� �ʱ�ȭ�ϰ� �߽��ϴ�.
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




// ���
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
		cout << "�ǰݴ���!" << endl;
		SetPlayerState(player, BeHitState::getInstance());
	}

}

void IdleState::stateRelease(Player* player)
{
	cout << "IdleState::release" << endl;

}

// �̵�
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

#pragma region ����Ű �Է¹޾� ������

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

#pragma region ����/��ų ��

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
		cout << "����!" << endl;
		SetPlayerState(player, BeHitState::getInstance());
	}

#pragma endregion 

#pragma region ������ ������Ʈ

	PLAYERDIRECTION temp;
	temp = player->getPlayerDirection();

	switch (temp)
	{
		// Y�����Ӹ� ����
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



// �ǰ�
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
	cout << "�¾��� �ФФФФФ�" << endl;
	// ������ �����ð� ����
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
	// ������ �̹��� ������ �� Ÿ��Ʋ�� �̵�
	cout << "����;;;;;;;;;;;;;;;;;;;;;;;" << endl; 

}

void DeadState::stateRelease(Player * player)
{
}


// ����
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
	cout << "1�� ����!!" << endl;
	if (KEYMANAGER->isStayKeyDown('X') )
	{
		SetPlayerState(player, Att2State::getInstance());
	}
	if (KEYOKU('X') )// && ������ ���� or ī��Ʈ ������ ��������� ��ȯ)
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
	if (KEYOKU('X'))// && ������ ���� or ī��Ʈ ������ ��������� ��ȯ)
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

	// if( ������ ���� or ī��Ʈ ������ ��������� ��ȯ)
	{
		player->setIsAttacking(false);
		SetPlayerState(player, IdleState::getInstance());
	}
}

void Att3State::stateRelease(Player * player)
{
}

// ��ų =========================================================
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