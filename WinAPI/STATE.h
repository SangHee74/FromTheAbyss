#pragma once
#include "Player.h"



class STATE
{
public:
	STATE() {}
	virtual ~STATE() {}

	// �������� �Լ�
	virtual void stateInit(Player* player)=0;
	virtual void stateUpdate(Player* player)=0;
	virtual void stateRelease()=0;
	virtual void stateRender(Player* player)=0;
 

protected:

	void SetPlayerState(Player* player, STATE* state)
	{
		player->setPlayerState(state);
	}

};

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


#pragma region attack
// ���� ���� - ����Ÿ�Կ� ���� �޺� ����Ƚ���� �޶�����.
class OneHandWeaponCombo : public STATE
{
	static OneHandWeaponCombo* instance;
	int timeCount;
	bitset<3> combo;
public:
	static OneHandWeaponCombo* getInstance();

	virtual void stateInit(Player* player);	  // �ʱ�ȭ
	virtual void stateUpdate(Player* player);  // ������Ʈ 
	virtual void stateRelease(); // ����

	void comboOne(Player* player);
	void comboTwo(Player* player);
	void comboThree(Player* player);
};


class TwoHandWeaponCombo : public STATE
{
	static TwoHandWeaponCombo* instance;
	int timeCount;
public:
	static TwoHandWeaponCombo* getInstance();

	virtual void stateInit(Player* player);	  // �ʱ�ȭ
	virtual void stateUpdate(Player* player);  // ������Ʈ 
	virtual void stateRelease(); // ����
};

#pragma region Skill

class SoulCapture : public STATE
{
	static SoulCapture* instance;
	int timeCount;
public:
	static SoulCapture* getInstance();

	virtual void stateInit(Player* player);	  // �ʱ�ȭ
	virtual void stateUpdate(Player* player);  // ������Ʈ 
	virtual void stateRelease(); // ����
};

class SpearStrike : public STATE
{
	static SpearStrike* instance;
	int timeCount;
public:
	static SpearStrike* getInstance();

	virtual void stateInit(Player* player);	  // �ʱ�ȭ
	virtual void stateUpdate(Player* player);  // ������Ʈ 
	virtual void stateRelease(); // ����
};
#endif

#pragma endregion 


