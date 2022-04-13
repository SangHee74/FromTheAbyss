#pragma once
#include "Monster.h"

class Minotaur : public Monster
{
private:
	int _endX;
	int _endY;


public:
	Minotaur();
	~Minotaur() {}

	void move();
	void attack();
	void speedUp();
	void setCollisionRange();
	void monsterMovetoPlayer();

};
