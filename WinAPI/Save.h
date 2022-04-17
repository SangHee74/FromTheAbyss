#pragma once
#include "GameNode.h"

enum SAVESLOT
{
	SAVE_ONE,SAVE_TWO,SAVE_THREE,SAVE_END
};

enum SAVETEXT
{
	NAME, ABYSS, TIME, SAVETEXT_END
};

struct tagSlot
{
	tagOnlyText txet[SAVETEXT_END];
	string info[SAVETEXT_END];
	RECT slotRc;
	Image* newGame;
	Image* newGameSelect;
	bool isSaved;
	bool isSelected;
};

class Save :public GameNode
{
private:
	tagSlot _slot[SAVE_END];
	RECT _selectRc;
	RECT _deleteRc;

	bool _nextScene;
	tagSceneFadeOut fadeOut;

public:
	Save() {}
	~Save() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void playerInfo(RECT rc);
};
