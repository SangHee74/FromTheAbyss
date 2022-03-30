#include "Stdafx.h"
#include "Idle.h"
#include "Player.h"

void Idle::enterState()
{
	//���¿� ������ �� ���¸��� �ʱ�ȭ�� ���ݴϴ� 
	//������ ���¿� ���� �̹��� ����� ���� index�� �ʱ�ȭ
	//_p->setPlayerFrameX(0);

}

void Idle::updateState()
{
	count++;
	// 30ī��Ʈ�� ������ ������ ���� �ٽ� 0���� �ʱ�ȭ �˴ϴ�
	// 30ī��Ʈ(0.5��)������ �� ���Է��ϸ� �����޺� ���°� �ǰ� ������ϴ�

	// ��� -> ����Ű ������ ������
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
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
		_p->setState(PLAYERSTATE::ATT);
	}
}

void Idle::exitState()
{
	count = 0;
}
