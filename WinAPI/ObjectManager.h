#pragma once
#include "SingletonBase.h"


class ObjectManager : public SingletonBase<ObjectManager>
{
private:

	Player* _player;
	EnemyManager* _em;

	// ������Ʈ 
	// 1. �� ���� ������Ʈ(����, �� ��) / ���� / �÷��̾�



public:
	ObjectManager() {}
	~ObjectManager() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	Player* getPlayer() { return _player; }
	EnemyManager* getEnemyManager() { return _em; }


	// �������� ����
	void renderSequenceCheck();

};

