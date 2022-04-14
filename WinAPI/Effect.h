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
	Image* img;
	RECT rc;
	int count;
	float x, y;
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

	Image* _image;
	RECT _rc;
	int _count;
	int _curFrameX;
	int _curFrameY;
	float _x, _y;
	bool _onEffect;


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


	void centerDamageEffect(int damage, POINT pos, DAMAGECOLOR color);
	bool getOnEffect() { return _onEffect; }

	//tagEffect&	   getTagEffect()     { return _collisionEff; }

};


class PlayerEffect 
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
	void draw(void);
	void removeEffect(int arrNum);

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

	void show(RECT rc);
	void draw(void);
	void removeEffect(int arrNum);

	MonsterEffect() {}
	~MonsterEffect() {}
};
