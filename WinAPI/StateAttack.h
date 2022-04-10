#pragma once
#include "STATE.h"

class Player;

// ���� ���� - ����Ÿ�Կ� ���� �޺� ����Ƚ���� �޶�����.
class OneHandWeaponCombo : public STATE
{
	static OneHandWeaponCombo* instance;
	//int _timeCount; 
	float _comboInputMinTime; // �ּ� Ű �Է� �ð�
	float _comboInputMaxTime; // �ִ� Ű �Է� �ð�

	// 001 : 1�� �޺�
	// 010 : 2�� �޺�
	// 100 : 3�� �޺� 
	bitset<3> _combo;
public:
	static OneHandWeaponCombo* getInstance();

	virtual void stateInit(Player* player);	  // �ʱ�ȭ
	virtual void stateUpdate(Player* player);  // ������Ʈ 
	virtual void stateRelease(); // ����
	virtual void stateRender(Player* player);


	void comboOne(Player* player);
	void comboTwo(Player* player);
	void comboThree(Player* player);
	void weaponAttFrameSetting(Player* player);
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
	virtual void stateRender(Player* player);

};

#if 0

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
	virtual void stateRender(Player* player);

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
	virtual void stateRender(Player* player);
};


#endif