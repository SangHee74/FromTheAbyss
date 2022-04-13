#pragma once
#include "Monster.h"

class Minotaur : public Monster
{
private:
	int _endX;
	int _endY;
	float _attTimeCount;

public:
	Minotaur();
	~Minotaur() {}

	void move();
	void attack();
	void speedUp();
	void setCollisionRange();
	void monsterMovetoPlayer();
	void drawEffect();
};
