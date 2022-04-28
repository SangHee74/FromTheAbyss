#pragma once
#include "GameNode.h"
#include "EnemyManager.h"
#include "SubMenu.h"

class StageBossIntro : public GameNode
{
private:

	SubMenu* _subScreen;
	Image* _playerImage;
	Image* _playerWeaponImage;

	//boss
	POINT  _bossPos;
	Image* _bossImage;
	Image* _bossName;
	int    _bossFrameX;
	int	   _bossFrameCount;
	int    _bossNameAlpha;
	bool   _eventStart;
	bool   _eventEnd;

	int   _firstUpdate;

	tagSceneFadeOut fadeOut;

public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void bossImageChange(bool skill = true);
	


};

