#pragma once
#include "GameNode.h"
#include "EnemyManager.h"
#include "ProgressBar.h"
#include "SubMenu.h"


class Stage : public GameNode
{
protected:

public:
	Stage() {}
	~Stage() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	virtual void portalOn();
	virtual void collision();
	virtual int playerRandomDamage();
	virtual int monsterRandomDamage(int i);
};

