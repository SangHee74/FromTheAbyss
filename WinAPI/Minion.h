#pragma once
#include "Enemy.h"


class Minion :public Enemy
{
public :
	Minion();
	~Minion();
};

// ������ ��ü�� �����̷��� �Ѵٸ� Ŭ������ ����
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


