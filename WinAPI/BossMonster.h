#pragma once
#include "Monster.h"

class Minotaur : public Monster
{
private:
	int _endX;
	int _endY;
	float _atkTimeCount;
	bool _atkStart;

public:
	Minotaur();
	~Minotaur() {}

	void move();
	void atkack();
	void drawEffect();
	void setCollisionAttRange();
	void setCollisionDefRange();

	void speedUp();
};
