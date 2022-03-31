#pragma once
#include "Player.h"
//#define STATEPATTERN

// �� ���� �ʿ�

#ifdef STATEPATTERN

class Player;

class STATE
{
protected:
	Player* _p;
	// ������ ���µ鿡�� �÷��̾ ��ũ�� �޾ƿ� �� �ְ� ��������ϴ�
public:
	~STATE();
	virtual void enterState() = 0;
	virtual void updateState() = 0;
	virtual void exitState() = 0;

	void linkMemberAdress(Player* player) { _p = player; }

};

#pragma region ���� Ŭ����
// ���/�̵�/�ǰ�/����
class Idle : public STATE
{
private:
	int count;
public:
	void enterState();
	void updateState();
	void exitState();
};

class Move : public STATE
{
private:
	int count;
public:
	void enterState();
	void updateState();
	void exitState();
};

class BeHit : public STATE
{
private:
	int count;
public:
	void enterState();
	void updateState();
	void exitState();
};

class DEAD : public STATE
{
private:
	int count;
public:
	void enterState();
	void updateState();
	void exitState();
};

// ���� =============================================================
class Att1 : public STATE
{
private:
	int count;
public:
	void enterState();
	void updateState();
	void exitState();
};

class Att2 : public STATE
{
private:
	int count;
public:
	void enterState();
	void updateState();
	void exitState();
};

class Att3 : public STATE
{
private:
	int count;
public:
	void enterState();
	void updateState();
	void exitState();
};

// ��ų =============================================================
class Skill1 : public STATE
{
private:
	int count;
public:
	void enterState();
	void updateState();
	void exitState();
};

class Skill2 : public STATE
{
private:
	int count;
public:
	void enterState();
	void updateState();
	void exitState();
};

class Skill3 : public STATE
{
private:
	int count;
public:
	void enterState();
	void updateState();
	void exitState();
};



#pragma endregion

#else 
class STATE
{
public:
	STATE() {}
	virtual ~STATE() {}

	// �������� �Լ�
	virtual void stateInit(Player* player)=0;
	virtual void stateUpdate(Player* player)=0;
	virtual void stateRelease()=0;

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
public:
	static IdleState* getInstance();

	virtual void stateInit(Player* player);	  // �ʱ�ȭ
	virtual void stateUpdate(Player* player);  // ������Ʈ 
	virtual void stateRelease(); // ����

};


// �̵� ���� 
class MoveState : public STATE
{
	static MoveState* instance;
public:
	static MoveState* getInstance();

	virtual void stateInit(Player* player);	  // �ʱ�ȭ
	virtual void stateUpdate(Player* player);  // ������Ʈ 
	virtual void stateRelease(); // ����
};


// �ǰ� ���� - �����ð����� ������ �� ����, Ű �Է��� ���� ��� ����Ѵ�.
class BeHitState : public STATE
{
	static BeHitState* instance;
public:
	static BeHitState* getInstance();

	virtual void stateInit(Player* player);	  // �ʱ�ȭ
	virtual void stateUpdate(Player* player);  // ������Ʈ 
	virtual void stateRelease(); // ����
};

// �ٿ� ���� - �����ð����� ������ ��� �� Ÿ��Ʋ�� ���ư���
class DeadState : public STATE
{
	static DeadState* instance;
public:
	static DeadState* getInstance();

	virtual void stateInit(Player* player);	  // �ʱ�ȭ
	virtual void stateUpdate(Player* player);  // ������Ʈ 
	virtual void stateRelease(); // ����
};


#pragma region attack
// ���� ���� - ����Ÿ�Կ� ���� �޺� ����Ƚ���� �޶�����.
class OneHandWeaponCombo : public STATE
{
	static OneHandWeaponCombo* instance;
public:
	static OneHandWeaponCombo* getInstance();

	virtual void stateInit(Player* player);	  // �ʱ�ȭ
	virtual void stateUpdate(Player* player);  // ������Ʈ 
	virtual void stateRelease(); // ����
};


class TwoHandWeaponCombo : public STATE
{
	static TwoHandWeaponCombo* instance;
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
public:
	static SoulCapture* getInstance();

	virtual void stateInit(Player* player);	  // �ʱ�ȭ
	virtual void stateUpdate(Player* player);  // ������Ʈ 
	virtual void stateRelease(); // ����
};

class SpearStrike : public STATE
{
	static SpearStrike* instance;
public:
	static SpearStrike* getInstance();

	virtual void stateInit(Player* player);	  // �ʱ�ȭ
	virtual void stateUpdate(Player* player);  // ������Ʈ 
	virtual void stateRelease(); // ����
};


#pragma endregion 


#endif // STATEPATTERN