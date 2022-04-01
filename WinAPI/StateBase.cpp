#include "Stdafx.h"
#include "StateBase.h"
#include "Player.h"


// ���, �̵�, �ǰ�, ���� ����
IdleState* IdleState::instance;
MoveState* MoveState::instance;
//BeHitState* BeHitState::instance;
//DeadState* DeadState::instance;


// ���
IdleState* IdleState::getInstance()
{
	if (instance == nullptr) instance = new IdleState();

	return instance;
}

void IdleState::stateInit(Player* player)
{
	cout << "IdleState::init" << endl;

	// �̹��� �̴�, ������ �ʱ�ȭ, ���ϸ��̼� �ʱ�ȭ ��
	//	player->getIsStateCheck().reset(2);


}

void IdleState::stateUpdate(Player* player)
{
	// timeCount 60 = 1��
	timeCount++;
	if (timeCount % 60 == 0); cout << "IdleState::update" << endl;

	// ������ �ƴҶ� �̵�
	if (!(player->getIsStateCheck().test(2)) &&
		( KEYMANAGER->isStayKeyDown(VK_LEFT)) || (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		|| (KEYMANAGER->isStayKeyDown(VK_UP)) || (KEYMANAGER->isStayKeyDown(VK_DOWN)))
	{
		cout << "get moveInstance" << endl;
		SetPlayerState(player, MoveState::getInstance());
	}

	/*
	// ����
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

	// ��ų
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		//SetPlayerState(player, SoulCapture::getInstance());
	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		// â�� �����ϰ� ������ ��ų��
		if (player->getPlayerWeapon() == WEAPONTYPE::SPEAR)
		{
			//SetPlayerState(player, SpearStrike::getInstance());
		}
	}
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		cout << "get 3rd Skill Instance" << endl;
	}

	// �ǰ�
	if (player->getIsStateCheck().test(3))
	{
		cout << "�ǰݴ���!" << endl;
		SetPlayerState(player, BeHitState::getInstance());
	}

	// ����
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

	// �÷��̾ ���� �Ʒ��� ����
	if (player->getPState().test(5))
	{



		//player->frameRender(getMemDC(), left, top, _frameX, _frameY);

	// �޸���, �ǰ�, ���� ����
	//if (_isStateCheck.test(1) || _isStateCheck.test(3) || !_isStateCheck.test(4))
	//{
	//}
	//else _weaponimage->frameRender(getMemDC(), weaponLeft, weaponTop, 1, _playerWeapon.frameY);
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
	player->getIsStateCheck().set(1);




}

void MoveState::stateUpdate(Player * player)
{
	timeCount++;
	if (timeCount % 120 == 0); cout << "MoveState::update" << endl;


	// ��
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
	// ��
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
	// ��
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
	// �Ʒ�
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

	//����Ű �Է� ����
	if (player->getIsStateCheck().test(1))
	{
		// �����·� ���ư��� ������ �����ؾߴ볪 ..
		// x�������� ��� ���� ���� �޸��� off ,
		// �޸��� ������ ����. 
		SetPlayerState(player, IdleState::getInstance());
	}

	/*
	// ����
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

	// ��ų
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		//SetPlayerState(player, SoulCapture::getInstance());
	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		// â�� �����ϰ� ������ ��ų��
		if (player->getPlayerWeapon() == WEAPONTYPE::SPEAR)
		{
		//	SetPlayerState(player, SpearStrike::getInstance());
		}
	}
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		cout << "get 3rd Skill Instance" << endl;
	}

	// �ǰ�
	if (player->getIsStateCheck().test(3))
	{
		cout << "�ǰݴ���!" << endl;
		SetPlayerState(player, BeHitState::getInstance());
	}

	// ����
	if (player->getStatus().curHp <= 0)
	{
		SetPlayerState(player, DeadState::getInstance());
	}

	*/

	if (timeCount % 10 == 0)
	{
		// �÷��̾� ����
		if (player->getIsStateCheck().test(0))
		{
			player->setPlayerFrameX(player->getPlayerFrameX() + 1);
			if (player->getPlayerFrameX() >= 3)
			{
				player->setPlayerFrameX(0);

				if (KEYOKU(VK_RIGHT) || KEYOKU(VK_LEFT) || KEYOKU(VK_UP) || KEYOKU(VK_DOWN))
				{
					// �������� ������ �� �������� Ű�� ���� �޸��� ����
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
					// �������� ������ �� �������� Ű�� ���� �޸��� ����
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
// �ǰ�
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
	if (timeCount % 120 == 0) cout << "�¾��� �ФФФФФ�" << endl;
	// ������ �����ð� ����

	// ���ʿ��� ������ ���������� �ణ �̵� 
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
	// ������ �̹��� ������ �� Ÿ��Ʋ�� �̵�
	cout << "����;;;;;;;;;;;;;;;;;;;;;;;" << endl;

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
