#pragma once
#include "GameNode.h"
#include "Enemy.h"
#include "Bullets.h"

class Rocket;

class EnemyManager : public GameNode
{
private:
	typedef vector<Enemy*> vEnemy;
	typedef vector<Enemy*>::iterator viEnemy;

private:
	vEnemy _vMinion;
	viEnemy _viMinion;

	Bullet* _bullet;
	Rocket* _rocket;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void setMinion(void);
	void removeMinion(int arrNum);

	void minionBulletFire(void);
	void collision(void);

	// 객체의 미니언이 어떤 객체와 충돌 했는지 등의 정보를 로켓으로 넘겨준다.
	vector<Enemy*> getMinions(void) { return _vMinion; }

	Bullet* getBullet(void) { return _bullet; }
	void setRocketMemoryAddress(Rocket* rk) { _rocket = rk; }

	EnemyManager() {}
	~EnemyManager() {}
};

