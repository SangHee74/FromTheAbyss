#pragma once
//#include "Player.h"
#define STATEPATTERN


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



class Idle : public STATE
{
private:
	int count;
public:
	void enterState();
	void updateState();
	void exitState();
};




#else 
class STATE
{
public:
	// ���¿� ���� �ൿ�� �Լ���
	virtual void idle(Player* player) =0;
	virtual void move(Player* player) =0;
	virtual void attack(Player* player) =0;
	virtual void beHit(Player* player) = 0;

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
	static IdleState* GetInstance();
	virtual void idle(Player* player);	 // ��� �� ��� 
	virtual void move(Player* player);	 // ��� �� �̵� -> ���º�ȭ(�����̱�)
	virtual void attack(Player* player); // ��� �� ���� -> ���º�ȭ(�����ϱ�)
	virtual void beHit(Player* player);	 // ��� �� �ǰ� -> ���º�ȭ(�ǰݸ��)

};

// �̵� ���� 
class MoveState : public STATE
{
	static MoveState* instance;
public:
	static MoveState* GetInstance();
	virtual void idle(Player* player);	 // �̵� �� ��� -> ���º�ȭ(����ϱ�)
	virtual void move(Player* player);	 // �̵� �� �̵�
	virtual void attack(Player* player); // �̵� �� ���� -> ���º�ȭ(�����ϱ�)
	virtual void beHit(Player* player);  // �̵� �� �ǰ� -> ���º�ȭ(�ǰݸ��)
};

// ���� ���� - ����Ÿ�Կ� ���� �޺� ����Ƚ���� �޶�����.
class AttackState : public STATE
{
	static AttackState* instance;
public:
	static AttackState* GetInstance();
	virtual void idle(Player* player);	 // ���� �� ��� -> ���º�ȭ(����ϱ�)
	virtual void move(Player* player);	 // ���� �� �̵� -> ���º�ȭ(�̵��ϱ�)
	virtual void attack(Player* player); // ���� �� ���� 
	virtual void beHit(Player* player);  // ���� �� �ǰ� -> ���º�ȭ(�ǰݸ��)

};

// �ǰ� ���� - �����ð����� ������ �� ����, Ű �Է��� ���� ��� ����Ѵ�.
class BeHitState : public STATE
{
	static BeHitState* instance;
public:
	static BeHitState* GetInstance();
	virtual void idle(Player* player);	 // �ǰ� �� ��� -> ���º�ȭ(����ϱ�)
	virtual void move(Player* player);	 // �ǰ� �� �̵� -> ���º�ȭ(�̵��ϱ�)
	virtual void attack(Player* player); // �ǰ� �� ���� -> ���º�ȭ(�����ϱ�)
	virtual void beHit(Player* player);  // �ǰ� �� �ǰ� 
};
#endif // STATEPATTERN