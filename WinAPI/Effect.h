#pragma once
#include "GameNode.h"

enum class EFFECT_TYPE
{
	P_ATKACK_ATKMOTION,   // ���¿��� ���� ����
	P_ATKACK_COLLISION,	  // �÷��̾�->���� Ÿ�ݼ���

	M_ATKACK_ATKMOTION,	  // ���� ���ݸ��
	M_ATKACK_COLLISION,	  // ����->�÷��̾� Ÿ�ݼ���

	M_DEFFENSE_DIE,		  // �ʵ���� ����
	M_DEFFENSE_BOSSDIE,	  // �������� ����
	EFFECT_END
};
enum class DAMAGECOLOR
{
	DAMAGE_WHITE, DAMAGE_RED, DAMAGE_GREEN, DAMAGE_BLUE,
	DAMAGE_END
};

class Effect 
{
public:
	Image* img;
	RECT rc;
	int count;
	int frameX;
	int posX, posY;
	bool onEffect;

	// damage 
	Image* damageFontImg;
	int damageNum;
	int numPosX, numPosY;
	bool onDmgNumEffect;

public:
	void baseEffSetting(RECT rc, EFFECT_TYPE type);
	void dmgEffSetting(int damage, POINT pos, DAMAGECOLOR color);
	
	void effUpdate();

	void baseEffRender();
	void dmgEffRender();


	Effect() :img(IMG("none")), rc(RectMake(0, 0, 0, 0)),
		count(0), frameX(0), posX(0), posY(0),
		onEffect(false),
		damageFontImg(IMG("none")),damageNum(0),
		numPosX(0), numPosY(0),	onDmgNumEffect(false)
	{}
	~Effect() {}
};
