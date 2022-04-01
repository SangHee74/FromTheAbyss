#pragma once
#include "STATE.h"

class Player;

// ��� ���� 
class IdleState : public STATE
{
	static IdleState* instance;
	int timeCount;
public:
	static IdleState* getInstance();

	virtual void stateInit(Player* player);	  // �ʱ�ȭ
	virtual void stateUpdate(Player* player);  // ������Ʈ 
	virtual void stateRelease(); // ����
	virtual void stateRender(Player* player);

};


// �̵� ���� 
class MoveState : public STATE
{
	static MoveState* instance;
	int timeCount;
public:
	static MoveState* getInstance();

	virtual void stateInit(Player* player);	  // �ʱ�ȭ
	virtual void stateUpdate(Player* player);  // ������Ʈ 
	virtual void stateRelease(); // ����
	virtual void stateRender(Player* player);
};


#if 0

// �ǰ� ���� - �����ð����� ������ �� ����, Ű �Է��� ���� ��� ����Ѵ�.
class BeHitState : public STATE
{
	static BeHitState* instance;
	int timeCount;

public:
	static BeHitState* getInstance();

	virtual void stateInit(Player* player);	  // �ʱ�ȭ
	virtual void stateUpdate(Player* player);  // ������Ʈ 
	virtual void stateRelease(); // ����
	virtual void stateRender();
};

// �ٿ� ���� - �����ð����� ������ ��� �� Ÿ��Ʋ�� ���ư���
class DeadState : public STATE
{
	static DeadState* instance;
	int timeCount;

public:
	static DeadState* getInstance();

	virtual void stateInit(Player* player);	  // �ʱ�ȭ
	virtual void stateUpdate(Player* player);  // ������Ʈ 
	virtual void stateRelease(); // ����
	virtual void stateRender();
};


#endif





