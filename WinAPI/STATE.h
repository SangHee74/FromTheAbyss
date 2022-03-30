#pragma once
#include "Player.h"
//#define STATEPATTERN


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
	// �������� �Լ�
	virtual void stateInit(Player* player)=0;
	virtual void stateUpdate(Player* player)=0;
	virtual void stateRelease(Player* player)=0;

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
	virtual void stateRelease(Player* player); // ����

};


// �̵� ���� 
class MoveState : public STATE
{
	static MoveState* instance;
public:
	static MoveState* getInstance();

	virtual void stateInit(Player* player);	  // �ʱ�ȭ
	virtual void stateUpdate(Player* player);  // ������Ʈ 
	virtual void stateRelease(Player* player); // ����
};

// ���� ���� - ����Ÿ�Կ� ���� �޺� ����Ƚ���� �޶�����.

class AttackState : public STATE
{
	static AttackState* instance;
public:
	static AttackState* getInstance();

	virtual void stateInit(Player* player);	  // �ʱ�ȭ
	virtual void stateUpdate(Player* player);  // ������Ʈ 
	virtual void stateRelease(Player* player); // ����
};

// �ǰ� ���� - �����ð����� ������ �� ����, Ű �Է��� ���� ��� ����Ѵ�.
class BeHitState : public STATE
{
	static BeHitState* instance;
public:
	static BeHitState* getInstance();

	virtual void stateInit(Player* player);	  // �ʱ�ȭ
	virtual void stateUpdate(Player* player);  // ������Ʈ 
	virtual void stateRelease(Player* player); // ����
};

#endif // STATEPATTERN