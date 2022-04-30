#pragma once
#include "STATE.h"

class Player;

// ���� ���� - ����Ÿ�Կ� ���� �޺� ����Ƚ���� �޶�����.
class OneHandWeaponCombo : public STATE
{
	static OneHandWeaponCombo* instance;
	float _comboInputMinTime; // �ּ� Ű �Է� �ð�
	float _comboInputMaxTime; // �ִ� Ű �Է� �ð�
	float _playerMotionTime;  // �÷��̾� ������ ����

	// 001 : 1�� �޺�
	// 010 : 2�� �޺�
	// 100 : 3�� �޺� 
	bitset<3> _comboStart;
	bitset<3> _comboEnd;

public:
	static OneHandWeaponCombo* getInstance();

	virtual void stateInit(Player* player);	  // �ʱ�ȭ
	virtual void stateUpdate(Player* player);  // ������Ʈ 
	virtual void stateRelease(); // ����
	virtual void stateRender(Player* player);

	void comboOne(Player* player);
	void comboTwo(Player* player);
	void comboThree(Player* player);
};


class TwoHandWeaponCombo : public STATE
{
	static TwoHandWeaponCombo* instance;
	float _comboInputMinTime; // �ּ� Ű �Է� �ð�
	float _comboInputMaxTime; // �ִ� Ű �Է� �ð�
	float _playerMotionTime;  // �÷��̾� ������ ����

	// 001 : 1�� �޺�
	// 010 : 2�� �޺�
	// 100 : 3�� �޺� 
	bitset<3> _comboStart;
	bitset<3> _comboEnd;


public:
	static TwoHandWeaponCombo* getInstance();

	virtual void stateInit(Player* player);	  // �ʱ�ȭ
	virtual void stateUpdate(Player* player);  // ������Ʈ 
	virtual void stateRelease(); // ����
	virtual void stateRender(Player* player);

	void comboOne(Player* player);


};