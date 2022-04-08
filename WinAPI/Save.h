#pragma once
#include "GameNode.h"

enum SAVESLOT
{
	SAVE_ONE,SAVE_TWO,SAVE_THREE,SAVE_END
};


struct tagSlot
{
	tagOnlyText txet;
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

public:
	Save() {}
	~Save() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};
