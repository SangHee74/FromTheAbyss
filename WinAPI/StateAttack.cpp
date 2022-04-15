#include "Stdafx.h"
#include "StateBase.h"
#include "StateAttack.h"
#include "Player.h"

// ���⺰ �޺�, ��ų���� 2�� 
OneHandWeaponCombo* OneHandWeaponCombo::instance;
TwoHandWeaponCombo* TwoHandWeaponCombo::instance;
//SoulCapture* SoulCapture::instance;
//SpearStrike* SpearStrike::instance;

// ����
OneHandWeaponCombo* OneHandWeaponCombo::getInstance()
{
	if (instance == nullptr) instance = new OneHandWeaponCombo();
	return instance;
}

void OneHandWeaponCombo::stateInit(Player* player)
{
	// �÷��̾� ���� ��Ʈ�� �ʱ�ȭ + �������� ��ȯ
	player->getIsStateCheck().reset();
	player->getIsStateCheck().set(2);

	player->getState() =PLAYERSTATE::ATK_ONEHANDCOMBO;
	
	player->getPlayerCollisionRc().atkEffFrameX = 0;
	player->getPlayerCollisionRc().atkEffFrameY = 0;
	player->getPlayerCollisionRc().atkPosX = 0;
	player->getPlayerCollisionRc().atkPosY = 0;
	player->getPlayerCollisionRc().atkWidth = 0;
	player->getPlayerCollisionRc().atkHeight = 0;

	
	// �޺� ��Ʈ�� �ʱ�ȭ + 1�� ���� ����
	_comboStart.reset();
	_comboStart.set(0);
	_comboEnd.reset(0);

	//_timeCount = 0;
	_comboInputMinTime = 0.0f;
	_comboInputMaxTime = 0.0f;
	_playerMotionTime = 0.0f;

	// ���⺰ ���� ������ ����(comboOne 1,2 /  comboTwo 1,2 / comboThree 1,2 ) : �� 6��
	// ����ġ�� �÷��̾� ���� �޾Ƽ� ����.

}

void OneHandWeaponCombo::stateUpdate(Player* player)
{
	// 60ī��Ʈ(1��)������ �� ���Է��ϸ� �����޺�
	// �޺����� �ð��� �ʱ�ȭ.

	_comboInputMaxTime += TIMEMANAGER->getElapsedTime();
	_comboInputMinTime += TIMEMANAGER->getElapsedTime();
	
	if (_comboStart.test(0)) comboOne(player);
	if (KEYSKD('x') && _comboInputMinTime > 0.5f && _comboEnd.test(0) )
	{
		player->getIsStateCheck().set(2);
		_comboInputMinTime = 0;
		_comboInputMaxTime = 0;
		cout << "�Ѽհ��� - 2�� �޺�" << endl;
		_comboStart.set(1);
	}
	if (KEYSKD('x') && _comboInputMinTime > 1.0f && _comboEnd.test(1) )
	{
		player->getIsStateCheck().set(2);
		_comboInputMinTime = 0;
		_comboInputMaxTime = 0;
		cout << "�Ѽհ��� - 3�� �޺�" << endl;
		_comboStart.set(2);
	}
	//cout << "--------------------------------------------------" << endl;
//	cout << "�޺� ������� �ɸ��� �ð� :" << _comboInputMinTime << endl;
	//������ ���� or ī��Ʈ ������ ��������� ��ȯ)
	if ( _comboInputMinTime > 0.7f					 // Ű�Է� �ð� �ʰ�
		 && !player->getIsStateCheck().test(2)    )  // ���ݻ��� �ƴ�
	{
		_comboStart.reset();
		_comboEnd.reset();

		cout << " Ű �Է� �ð��ʰ�! �����·� ��ȯ�մϴ�." << endl;
		SetPlayerState(player, IdleState::getInstance());

	}


}

void OneHandWeaponCombo::stateRelease()
{
	//if (instance)
	//{
	//	delete instance;
	//	instance = 0;
	//}
}

void OneHandWeaponCombo::stateRender(Player* player)
{
}

void OneHandWeaponCombo::comboOne(Player* player)
{
	// �¿� ��Ʈ��
	if (player->getDirection() == PLAYERDIRECTION::RIGHT
		|| player->getDirection() == PLAYERDIRECTION::RIGHTUP
		|| player->getDirection() == PLAYERDIRECTION::RIGHTDOWN)
	{
	//	cout << "��������! �������� 1���� ����, -1" << endl;
	}
	else
	{
		player->getIsStateCheck().set(0);
	//	cout << "������!!!!! �������� 0���� ����, +1" << endl;
	}


	// �̹��� ���� 
	player->getPlayer().image = IMG("p_oneHandCombo_01");
	player->getPlayerCollisionRc().atkEffectImg = IMG("eff_sword");

	
	// ������ ����  
	// 1�޺� ù��° ������ 
	if (_playerMotionTime <= 3.0f)
	{
		if (player->getIsStateCheck().test(0)) // L
		{
		//	cout << "player FrameX 1-1 , Left " << endl;
			_playerMotionTime++; // �������� �ִ� ��쿡�� ����
			player->getPlayer().frameX = 0;
			player->getPlayerCollisionRc().atkEffFrameX = 1;
			player->getPlayerCollisionRc().atkEffFrameY = 1;
		}
		if (!player->getIsStateCheck().test(0)) // R
		{
		//	cout << "player FrameX 1-1 , Right " << endl;
			_playerMotionTime++;
			player->getPlayer().frameX = 1;						// ĳ���� ������
			player->getPlayerCollisionRc().atkEffFrameX = 0;	// ����Ʈ ������ 
			player->getPlayerCollisionRc().atkEffFrameY = 0;

		}
		// �޺�-������ �� ���� ������ ������Ʈ + Ÿ�ݹ��� ������Ʈ
		player->playerAttSetting(_comboStart);						// ���ݹ��� ������Ʈ 		
	}


	// 1�޺� �ι�° ������
	if (_playerMotionTime >= 3.1f && _playerMotionTime <= 7.4f)
	{
		_comboInputMaxTime = 0;
		// �����̰�, �޺� 1�� ����
		if (player->getIsStateCheck().test(0) && _comboStart.test(0)) // L
		{
		//	cout << "player FrameX 1-2 , Left " << endl;
			_playerMotionTime++;
			player->getPlayer().frameX += 1;
			player->getPlayerCollisionRc().atkEffFrameX += 1;
			if (player->getPlayer().frameX == player->getPlayer().image->getMaxFrameX())
			{
				player->getPlayer().frameX = player->getPlayer().image->getMaxFrameX();
				//_comboInputMaxTime++;
			}
		}
		// �������̰�, �޺� 1�� ����
		if (!player->getIsStateCheck().test(0) && _comboStart.test(0)) // R 
		{
		//	cout << "player FrameX 1-2 , Right " << endl;
			_playerMotionTime++;
			player->getPlayer().frameX -= 1;
			player->getPlayerCollisionRc().atkEffFrameX -= 1;
			if (player->getPlayer().frameX < 0)
			{
				player->getPlayer().frameX = 0;
				//_comboInputMaxTime++;
			}
		}
		player->playerAttSetting(_comboStart);
	}


	if (_playerMotionTime > 7.5f)			// �޺� 1�� ����� ��� ������
	{
		_comboEnd.set(0);				    // 1���޺� �����
		player->getIsStateCheck().reset(2); // ���ݻ��� ����
	//	cout << "1�� �޺� ����� " << endl;


	}


}

void OneHandWeaponCombo::comboTwo(Player* player)
{
	player->getPlayer().image = IMG("p_oneHandCombo_02");

	player->getIsStateCheck().set(2);

	cout << "�Ѽչ��� 2�� ���� �Լ�" << endl;


}

void OneHandWeaponCombo::comboThree(Player* player)
{
	player->getPlayer().image = IMG("p_oneHandCombo_03");

	player->getIsStateCheck().set(2);

	cout << "�Ѽչ��� 3�� ���� �Լ�" << endl;


}


TwoHandWeaponCombo * TwoHandWeaponCombo::getInstance()
{
	if (instance == nullptr) instance = new TwoHandWeaponCombo();
	return instance;
}

void TwoHandWeaponCombo::stateInit(Player* player)
{
	// ��Ʈ�� �ʱ�ȭ + �������� ��ȯ
	player->getIsStateCheck().reset(0);
	player->getIsStateCheck().set(2);
	
	timeCount = 0;
}

void TwoHandWeaponCombo::stateUpdate(Player* player)
{

	// 30ī��Ʈ(0.5��)������ �� ���Է��ϸ� �����޺�
	timeCount++;
	player->getPlayer().image = IMG("p_oneHandCombo_02");

	cout << "�μչ��� 1�� ����" << endl;
	if (KEYMANAGER->isStayKeyDown('X'))
	{
		// 2�� ���� ����

	}
	//������ ���� or ī��Ʈ ������ ��������� ��ȯ)
	if (KEYOKU('X') && timeCount >= 30)
	{
		SetPlayerState(player, IdleState::getInstance());
	}
}

void TwoHandWeaponCombo::stateRelease()
{
	if (instance)
	{
		delete instance;
		instance = 0;
	}
}

void TwoHandWeaponCombo::stateRender(Player* player)
{
}

#if 0
// ��ų =========================================================
SoulCapture* SoulCapture::getInstance()
{
	if (instance == nullptr) instance = new SoulCapture();
	return instance;
}

void SoulCapture::stateInit(Player * player)
{
	// ��Ʈ�� �ʱ�ȭ + �������� ��ȯ
	player->getIsStateCheck().reset(0);
	player->getIsStateCheck().set(2);

	player->setPlayerImg(IMG("p_skill_soulCapture"));

}

void SoulCapture::stateUpdate(Player * player)
{
	// 30ī��Ʈ(0.5��)������ �� ���Է��ϸ� �����޺�
	timeCount++;

	cout << "��ų : �ҿ�ĸ�� ���� " << endl;
	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		// XŰ ��Ÿ�� �ҿ�ĸ�� ������ �� ����
	}

	// �ҿ� ĸ�� �����(�����ʿ�)
	if (KEYOKU('X') && timeCount >= 30)
	{
		SetPlayerState(player, IdleState::getInstance());
	}
	//	if (_player.frameX > 1 ) _player.frameX = 0;

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
	// �����ʿ�~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// ��Ʈ�� �ʱ�ȭ + �������� ��ȯ
	player->getIsStateCheck().reset(0);
	player->getIsStateCheck().set(2);

	player->setPlayerImg(IMG("p_skill_soulCapture"));
	//	if (_player.frameX > 1) _player.frameX = 0;

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
#endif 