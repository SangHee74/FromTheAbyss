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


	ProgressBar() {}
	virtual ~ProgressBar() {}
};

