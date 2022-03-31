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
OneHandWeaponCombo* OneHandWeaponCombo::instance;
TwoHandWeaponCombo* TwoHandWeaponCombo::instance;
SoulCapture* SoulCapture::instance;
SpearStrike* SpearStrike::instance;


// ���
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
		//if �Ѽչ����
		SetPlayerState(player, OneHandWeaponCombo::getInstance());
		// else �μչ����
		//SetPlayerState(player, TwoHandWeaponCombo1::getInstance());

	}

	if (KEYMANAGER->isStayKeyDown('A'))
	{
		SetPlayerState(player, SoulCapture::getInstance());
	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		
		// if â�� ������ �ִ���
		SetPlayerState(player, SpearStrike::getInstance());
	}
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		cout << "get 3rd Skill Instance" << endl;
	}

	if (player->getIsHit())
	{
		cout << "�ǰݴ���!" << endl;
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

#pragma region ����/��ų ��

	if (KEYMANAGER->isStayKeyDown('X'))
	{
		cout << "get Att1Instance!!!!!" << endl;
		player->setIsAttacking(true);
		//if �Ѽչ����
		SetPlayerState(player, OneHandWeaponCombo::getInstance());
		// else �μչ����
		//SetPlayerState(player, TwoHandWeaponCombo1::getInstance());

	}

	if (KEYMANAGER->isStayKeyDown('A'))
	{
		SetPlayerState(player, SoulCapture::getInstance());
	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{

		// if â�� ������ �ִ���
		SetPlayerState(player, SpearStrike::getInstance());
	}
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		cout << "get 3rd Skill Instance" << endl;
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

void MoveState::stateRelease()
{
	cout << "MoveState::release" << endl;

	if (instance)
	{
		delete instance;
		instance = 0;
	}
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
	// ������ �̹��� ������ �� Ÿ��Ʋ�� �̵�
	cout << "����;;;;;;;;;;;;;;;;;;;;;;;" << endl; 

}

void DeadState::stateRelease()
{
}


// ����
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
	cout << "1�� ����!!" << endl;
	if (KEYMANAGER->isStayKeyDown('X') )
	{
		// 2�� ���� ����

	}
	if (KEYOKU('X') )// && ������ ���� or ī��Ʈ ������ ��������� ��ȯ)
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


// ��ų =========================================================
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
