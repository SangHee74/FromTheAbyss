#pragma once
#include "SingletonBase.h"


class ObjectManager : public SingletonBase<ObjectManager>
{
private:

	Player* _player;
	EnemyManager* _em;

	// 오브젝트 
	// 1. 맵 렌더 오브젝트(나무, 돌 등) / 몬스터 / 플레이어



public:
	ObjectManager() {}
	~ObjectManager() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	Player* getPlayer() { return _player; }
	EnemyManager* getEnemyManager() { return _em; }


	// 렌더순서 정렬
	void renderSequenceCheck();

};

