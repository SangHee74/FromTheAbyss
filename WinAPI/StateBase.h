#pragma once
#include "STATE.h"

class Player;

// ��� ���� 
class IdleState : public STATE, public GameNode
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
	//int frameCount;
	int frameIndexX;
public:
	static MoveState* getInstance();

	virtual void stateInit(Player* player);	  // �ʱ�ȭ
	virtual void stateUpdate(Player* player);  // ������Ʈ 
	virtual void stateRelease(); // ����
	virtual void stateRender(Player* player);

	void pixelCollision(Player* player); // �ȼ��浹 ����
	bool pixelColorCheck(int getPixelX, int getPixelY); // �ȼ��浹 üũ
};



// �ǰ� ���� - �����ð����� ������ �� ����, Ű �Է��� ���� ��� ����Ѵ�.
class HitState : public STATE
{
	static HitState* instance;
	int timeCount;

public:
	static HitState* getInstance();

	virtual void stateInit(Player* player);	  // �ʱ�ȭ
	virtual void stateUpdate(Player* player);  // ������Ʈ 
	virtual void stateRelease(); // ����
	virtual void stateRender(Player* player);
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
	virtual void stateRender(Player* player);
};





