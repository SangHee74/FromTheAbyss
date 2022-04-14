#pragma once
#include "GameNode.h"


enum class EFFECT_TYPE
{
	//P_EFFECT_ATTMOTION, // ���¿��� ���� ����
	P_EFFECT_COLLISION,	  // �÷��̾�->���� Ÿ�ݼ���

	M_EFFECT_ATTMOTION,	  // ���� ���ݸ��
	M_EFFECT_COLLISION,	  // ����->�÷��̾� Ÿ�ݼ���

	M_EFFECT_DIE,		  // �ʵ���� ����
	M_EFFECT_BOSSDIE,	  // �������� ����
	EFFECT_END
};

struct tagEffect
{
	Image* image;
	RECT rc;
	int count;
	int curFrameX;
	int curFrameY;
	float x, y;
	bool onEffect;

};

enum class DAMAGECOLOR
{
	DAMAGE_WHITE, DAMAGE_RED, DAMAGE_GREEN, DAMAGE_BLUE,
	DAMAGE_END
};

class Effect :public GameNode
{
private:
	tagEffect	  _collisionEff;

public:

	Effect();
	~Effect() {}

	HRESULT init(void);
	HRESULT init(const char* imageKey, RECT rc);
	void release(void);
	void update(void);
	void render(void);

	void draw(void);
	void animation(void);
	virtual void aniEff(tagEffect eff, int speed);

	tagEffect&	   getTagEffect()     { return _collisionEff; }
	void centerDamageEffect(int damage, POINT pos, DAMAGECOLOR color);
};


class PlayerEffect : public Effect
{
private:
	vector<tagEffect> _vEffect;
	vector<tagEffect>::iterator _viEffect;

public:

	HRESULT init(void);
	HRESULT init(RECT rc, const char* imageKey);
	void release(void);
	void update(void);
	void render(void);

	void show(RECT rc);
	void show(RECT rc, const char* imageKey);
	void draw(void);
	void removeEffect(int arrNum);

	PlayerEffect() {}
	~PlayerEffect() {}
};


class MonsterEffect : public Effect
{
private:
	vector<tagEffect> _vEffect;
	vector<tagEffect>::iterator _viEffect;

public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void show(RECT rc);
	void show(RECT rc, const char* imageKey);
	void draw(void);
	void removeEffect(int arrNum);

	MonsterEffect() {}
	~MonsterEffect() {}
};
