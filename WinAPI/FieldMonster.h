#pragma once
#include "Monster.h"

class Dionaea : public Monster
{
private:

public:
	Dionaea();
	~Dionaea() {};

	void move();
	void attack();

};


class EvilEye : public Monster
{
private:

public:
	EvilEye();
	~EvilEye() {};

	void move();
	void attack();

};

class Kobold : public Monster
{
private:

public:
	Kobold();
	~Kobold() {};

	void move();
	void attack();

}; 