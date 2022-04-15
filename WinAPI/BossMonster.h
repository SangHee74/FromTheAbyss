#pragma once
#include "Monster.h"

class Minotaur : public Monster
{
private:
	int _endX;
	int _endY;
	float _attTimeCount;
	bool _attStart;

public:
	Minotaur();
	~Minotaur() {}

	void move();
	void attack();
	void drawEffect();
	void setCollisionAttRange();
	void setCollisionDefRange();

	void speedUp();
};
