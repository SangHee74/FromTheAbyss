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
	

	player->getPlayerCollisionRc().attEffFrameX = 0;
	player->getPlayerCollisionRc().attEffFrameY = 0;
	player->getPlayerCollisionRc().attPosX = 0;
	player->getPlayerCollisionRc().attPosY = 0;
	player->getPlayerCollisionRc().attWidth = 0;
	player->getPlayerCollisionRc().attHeight = 0;

	
	// �޺� ��Ʈ�� �ʱ�ȭ + 1�� ���� ����
	_combo.reset(0);
	_combo.set(0);

	//_timeCount = 0;
	_comboInputMinTime = 0.0f;
	_comboInputMaxTime = 0.0f;

	// ���⺰ ���� ������ ����(comboOne 1,2 /  comboTwo 1,2 / comboThree 1,2 ) : �� 6��
	// ����ġ�� �÷��̾� ���� �޾Ƽ� ����.

}

void OneHandWeaponCombo::stateUpdate(Player* player)
{

	// 60ī��Ʈ(1��)������ �� ���Է��ϸ� �����޺�
	// �޺����� �ð��� �ʱ�ȭ.

	// 
	_comboInputMaxTime += TIMEMANAGER->getElapsedTime();
	_comboInputMinTime += TIMEMANAGER->getElapsedTime();
	//if (_comboInputMaxTime >= 1.7f && (! player->getIsStateCheck().test(2)))
	if (_comboInputMaxTime >= 5.7f && (! player->getIsStateCheck().test(2)))
	{
		_comboInputMaxTime = 0;
		cout << " Ű �Է� �ð��ʰ�! �����·� ��ȯ�մϴ�." << endl;
		SetPlayerState(player, IdleState::getInstance());
	}

	if (_combo.test(0)) comboOne(player);
	if (KEYSKD('x') && _comboInputMinTime > 0.5f && _combo.test(0) )
	{
		player->getIsStateCheck().set(2);
		_comboInputMinTime = 0;
		_comboInputMaxTime = 0;
		cout << "�Ѽհ��� - 2�� �޺�" << endl;
		_combo.set(1);
	}
	if (KEYSKD('x') && _comboInputMinTime > 1.0f && _combo.test(1) )
	{
		_comboInputMinTime = 0;
		_comboInputMaxTime = 0;
		cout << "�Ѽհ��� - 3�� �޺�" << endl;
		_combo.set(2);
	}

	//if (combo.test(0) && KEYMANAGER->isStayKeyDown('X') && !player->getIsStateCheck().test(2))
	{
		// 2�� ���� ����
		//combo.set(1);
		//comboTwo(player);
		//combo.reset(0);
	}
	//else if (combo.test(1) && KEYMANAGER->isStayKeyDown('X') && !player->getIsStateCheck().test(2))
	{
		// 3�� ���� ����
		//combo.set(2);
		//comboThree(player);
		//combo.reset(1);
	}
	//������ ���� or ī��Ʈ ������ ��������� ��ȯ)
	if (_combo.test(2) && (_comboInputMinTime > 1.0f  &&  !player->getIsStateCheck().test(2))      )
	{
		_combo.reset();
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
	if (player->getDirection() == PLAYERDIRECTION::RIGHT
		|| player->getDirection() == PLAYERDIRECTION::RIGHTUP
		|| player->getDirection() == PLAYERDIRECTION::RIGHTDOWN)
	{
		cout << "��������! �������� 1���� ����, -1!!!!" << endl;
	}
	else
	{
		player->getIsStateCheck().set(0);
		cout << "������!!!!! �������� 1���� ����, +1!!!!" << endl;

	}


	// �̹��� ���� 
	player->getPlayer().image = IMG("p_oneHandCombo_01");
	player->getPlayerCollisionRc().attEffectImg = IMG("eff_sword");
	player->getPlayerCollisionRc().attEffFrameY = static_cast<int>(player->getDirection());

	// ������ ����  
	// 1�޺� ù��° ������ 
	if (_comboInputMaxTime < 0.3)
	{
		if (player->getIsStateCheck().test(0))
		{
			player->getPlayer().frameX = 1;
			player->getPlayerCollisionRc().attEffFrameX = 1;
		}
		if (!player->getIsStateCheck().test(0))
		{
			player->getPlayer().frameX = 0;						// ĳ���� ������
			player->getPlayerCollisionRc().attEffFrameX = 0;	// ����Ʈ ������ 
		}
		// �޺�-������ �� ���� ������ ������Ʈ + Ÿ�ݹ��� ������Ʈ
		player->playerAttSetting(_combo);						// ���ݹ��� ������Ʈ 		
	}



	// 1�޺� �ι�° ������
	if (_comboInputMaxTime >= 0.3)
	{
		if (player->getIsStateCheck().test(0)) // ���� 
		{
			player->getPlayer().frameX += 1;
			player->getPlayerCollisionRc().attEffFrameX += 1;
			if (player->getPlayer().frameX == player->getPlayer().image->getMaxFrameX())
			{
				player->getPlayer().frameX = player->getPlayer().image->getMaxFrameX();
			}
		}
		if (!player->getIsStateCheck().test(0)) // ������ 
		{
			player->getPlayer().frameX -= 1;
			player->getPlayerCollisionRc().attEffFrameX -= 1;
			if (player->getPlayer().frameX == player->getPlayer().image->getMaxFrameX())
			{
				player->getPlayer().frameX = player->getPlayer().image->getMaxFrameX();
			}
		}
		player->playerAttSetting(_combo);
	}

	player->getIsStateCheck().reset(2);

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