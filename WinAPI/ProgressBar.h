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

	Image* _progressBarUp;
	Image* _progressBarDown;
	RECT _rc;
	int _x;
	int _y;
	float _width;

public:
	HRESULT init(int x, int y, int width, int height); // boss (630,30)
	void release(void);
	void update(void);
	void render(void);

	void setBossHpGauge(float currentScore, float maxScore);

	void setX(int x) { _x = x; }
	void setY(int y) { _y = y; }


	ProgressBarBoss() {}
	virtual ~ProgressBarBoss() {}


};


