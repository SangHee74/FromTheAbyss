#pragma once
#include "Monster.h"

class Minotaur : public Monster
{
private:



public:
	Minotaur();
	~Minotaur() {}

	void move();
	void attack();
	void speedUp();
	

};
