#pragma once
#include "GameNode.h"

enum class EFFECT_TYPE
{
	P_ATKACK_ATKMOTION, // ���¿��� ���� ����
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

struct tagEffect
{
	Image* img;
	RECT rc;
	int count;
	int curFrameX;
	int curFrameY;
	float x, y;
	bool onEffect;
};

class PlayerEffect :public GameNode
{
private:
	vector<tagEffect> _vEffect;
	vector<tagEffect>::iterator _viEffect;

public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void createEff(RECT rc, EFFECT_TYPE type); // ����Ʈ �̹���, ������Ʈ(+ī�޶�����) ������Ʈ 
	void draw(void);
	void removeEffect(int arrNum);

	void centerDamageEffect(int damage, POINT pos, DAMAGECOLOR color);

	PlayerEffect() {}
	~PlayerEffect() {}
};


class MonsterEffect :public GameNode
{
private:
	vector<tagEffect> _vEffect;
	vector<tagEffect>::iterator _viEffect;

public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void createEff(RECT rc, EFFECT_TYPE type); // ����Ʈ �̹���, ������Ʈ(+ī�޶�����) ������Ʈ 
	void draw(void);
	void removeEffect(int arrNum);

	void centerDamageEffect(int damage, POINT pos);

	MonsterEffect() {}
	~MonsterEffect() {}
};
