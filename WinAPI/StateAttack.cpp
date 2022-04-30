#include "Stdafx.h"
#include "StateBase.h"
#include "StateAttack.h"
#include "Player.h"

// ���⺰ �޺�,
OneHandWeaponCombo* OneHandWeaponCombo::instance;
TwoHandWeaponCombo* TwoHandWeaponCombo::instance;


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

}

void OneHandWeaponCombo::stateUpdate(Player* player)
{
	// 60ī��Ʈ(1��)������ �� ���Է��ϸ� �����޺�
	// �޺����� �ð��� �ʱ�ȭ.

	_comboInputMaxTime += TIMEMANAGER->getElapsedTime();
	_comboInputMinTime += TIMEMANAGER->getElapsedTime();
	
	if (_comboStart.test(0)) comboOne(player);
	
	if ( _comboInputMinTime > 2.4f					 // Ű�Է� �ð� �ʰ�
		 && !player->getIsStateCheck().test(2)    )  // ���ݻ��� �ƴ�
	{
		_comboStart.reset();
		_comboEnd.reset();

		SetPlayerState(player, IdleState::getInstance());
	}

	// �޺� �ð� �� Ÿ�ݹ��� ������Ʈ ���� 
	if (_playerMotionTime >= 0.9f && _playerMotionTime <= 1.0f) player->getPlayerCollisionRc().atkRangeUpdate = true;
	if (_playerMotionTime >= 1.8f) player->getPlayerCollisionRc().atkRangeUpdate = false;


	// �޺�-������ �� ���� ������ ������Ʈ + Ÿ�ݹ��� ������Ʈ
	player->playerAttSetting(_comboStart);					// ���ݹ��� ������Ʈ 		
	
}

void OneHandWeaponCombo::stateRelease()
{

}

void OneHandWeaponCombo::stateRender(Player* player)
{
}

void OneHandWeaponCombo::comboOne(Player* player)
{
	// �̹��� ���� 
	player->getPlayer().image = IMG("p_oneHandCombo_01");

	// ������ ����  
	// 1�޺� ù��° ������ 
	if (_playerMotionTime <= 1.0f)
	{
		if (player->getIsStateCheck().test(0)) // L
		{
			_playerMotionTime+=TIMEMANAGER->getElapsedTime(); // �������� �ִ� ��쿡�� ����
			player->getPlayer().frameX = 0;
		}
		if (!player->getIsStateCheck().test(0)) // R
		{
			_playerMotionTime += TIMEMANAGER->getElapsedTime();
			player->getPlayer().frameX = 1;						// ĳ���� ������
		}
	}

	// 1�޺� �ι�° ������
	if (_playerMotionTime >= 1.0f && _playerMotionTime <= 2.4f)
	{
		_comboInputMaxTime = 0;
		// �����̰�, �޺� 1�� ����
		if (player->getIsStateCheck().test(0) && _comboStart.test(0)) // L
		{
			_playerMotionTime += TIMEMANAGER->getElapsedTime();
			player->getPlayer().frameX = 1;
		}
		// �������̰�, �޺� 1�� ����
		if (!player->getIsStateCheck().test(0) && _comboStart.test(0)) // R 
		{
			_playerMotionTime += TIMEMANAGER->getElapsedTime();
			player->getPlayer().frameX = 0;
		}
	}

	if (_playerMotionTime >= 2.4f)			// �޺� 1�� ����� ��� ������
	{
		_comboEnd.set(0);				    // 1���޺� �����
		player->getIsStateCheck().reset(2); // ���ݻ��� ����
	}

}

void OneHandWeaponCombo::comboTwo(Player* player)
{
	player->getPlayer().image = IMG("p_oneHandCombo_02");
	player->getIsStateCheck().set(2);

}

void OneHandWeaponCombo::comboThree(Player* player)
{
	player->getPlayer().image = IMG("p_oneHandCombo_03");
	player->getIsStateCheck().set(2);

}


TwoHandWeaponCombo * TwoHandWeaponCombo::getInstance()
{
	if (instance == nullptr) instance = new TwoHandWeaponCombo();
	return instance;
}

void TwoHandWeaponCombo::stateInit(Player* player)
{
	// �÷��̾� ���� ��Ʈ�� �ʱ�ȭ + �������� ��ȯ
	player->getIsStateCheck().reset();
	player->getIsStateCheck().set(2);

	player->getState() = PLAYERSTATE::ATK_ONEHANDCOMBO;

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
}

void TwoHandWeaponCombo::stateUpdate(Player* player)
{

	_comboInputMaxTime += TIMEMANAGER->getElapsedTime();
	_comboInputMinTime += TIMEMANAGER->getElapsedTime();

	if (_comboStart.test(0)) comboOne(player);

	if (_comboInputMinTime > 2.4f && !player->getIsStateCheck().test(2))	
	{
		_comboStart.reset();
		_comboEnd.reset();
		SetPlayerState(player, IdleState::getInstance());
	}

	if (_playerMotionTime >= 0.9f && _playerMotionTime <= 1.0f) player->getPlayerCollisionRc().atkRangeUpdate = true;
	if (_playerMotionTime >= 1.8f) player->getPlayerCollisionRc().atkRangeUpdate = false;

	player->playerAttSetting(_comboStart);
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

void TwoHandWeaponCombo::comboOne(Player * player)
{
	// �̹��� ���� 
	player->getPlayer().image = IMG("p_twoHandCombo_01");


	// ������ ����  
	if (_playerMotionTime <= 1.0f) // 1 combo 1st FrameX
	{
		if (player->getIsStateCheck().test(0)) // L
		{
			_playerMotionTime += TIMEMANAGER->getElapsedTime();
			player->getPlayer().frameX = 0;
		}
		if (!player->getIsStateCheck().test(0)) // R
		{
			_playerMotionTime += TIMEMANAGER->getElapsedTime();
			player->getPlayer().frameX = 1;
		}
	}

	if (_playerMotionTime >= 1.0f && _playerMotionTime <= 2.4f) // 1 combo 2nd FrameX
	{
		_comboInputMaxTime = 0;
		if (player->getIsStateCheck().test(0) && _comboStart.test(0)) // L
		{
			_playerMotionTime += TIMEMANAGER->getElapsedTime();
			player->getPlayer().frameX = 1;
		}
		if (!player->getIsStateCheck().test(0) && _comboStart.test(0)) // R 
		{
			_playerMotionTime += TIMEMANAGER->getElapsedTime();
			player->getPlayer().frameX = 0;
		}
	}
	if (_playerMotionTime >= 2.3f)
	{
		_comboEnd.set(0);
		player->getIsStateCheck().reset(2);
	}
}
