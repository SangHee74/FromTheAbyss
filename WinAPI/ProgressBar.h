#pragma once
#include "GameNode.h"

class ProgressBar : public GameNode
{
private:

	RECT _hpRc;
	RECT _spRc;

	int  _x, _y;
	float _hpWidth;
	float _spWidth;

	Image* _hpBarCover;
	Image* _hpBar;
	Image* _spBarCover;
	Image* _spBar;

	POINT _hpPos;
	POINT _mpPos;

public:

	HRESULT init(float hp, float sp ); // player
	void release(void);
	void update(void);
	void render(void);

	void setHpGauge(float currentScore, float maxScore);
	void setSpGauge(float currentScore, float maxScore);

	void setX(int x) { _x = x; }
	void setY(int y) { _y = y; }

	void renderHpSpNumImg(int curHp, int curSp, int MaxHp, int MaxSp);


	ProgressBar() {}
	virtual ~ProgressBar() {}
};



class ProgressBarBoss : public GameNode
{
private:

	int _x;
	int _y;

	RECT _rc;
	float _hpMaxWidth;
	float _hpWidth;

	Image* _hpBarBg;
	Image* _hpBar;


public:
	HRESULT init(float hp); // boss
	void release(void);
	void update(void);
	void render(void);

	void setGauge(float currentScore, float maxScore);
	void setBossHpGauge(float hpScore);
	POINT getHpMpBar();

	void setX(int x) { _x = x; }
	void setY(int y) { _y = y; }

public:
	ProgressBarBoss() {}
	virtual ~ProgressBarBoss() {}

	float getHpWidth() { return _hpWidth; }
};



