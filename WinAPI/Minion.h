#pragma once
#include "Enemy.h"


class Minion :public Enemy
{
public :
	Minion();
	~Minion();
};

// 각각의 객체를 움직이려고 한다면 클래스를 복제
class Minion2 :public Enemy
{
private:

public:
	Minion2();
	 ~Minion2() {};

	virtual void move(void);
};

class Minion3 :public Enemy
{
public:
	Minion3() {};
	~Minion3() {};

	virtual void move(void);
};


