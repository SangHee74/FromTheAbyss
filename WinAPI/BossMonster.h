#pragma once
#include "Monster.h"

class Minotaur : public Monster
{
private:
	int _endX;
	int _endY;
	float _atkTimeCount;
	bool _atkStart;
	bool _offEff;

public:
	Minotaur();
	~Minotaur() {}

	virtual void move();
	virtual void attack();
	virtual void imgUpdate();
	virtual void rectUpdate();
	virtual void draw();

	void speedUp();
};
