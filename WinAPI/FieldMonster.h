#pragma once
#include "Monster.h"

class Dionaea : public Monster
{
private:

public:
	Dionaea();
	~Dionaea() {};

	void move();
	void atkack();

};


class EvilEye : public Monster
{
private:

public:
	EvilEye();
	~EvilEye() {};

	void move();
	void atkack();

};

class Kobold : public Monster
{
private:

public:
	Kobold();
	~Kobold() {};

	void move();
	void atkack();

}; 