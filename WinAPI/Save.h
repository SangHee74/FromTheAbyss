#pragma once
#include "GameNode.h"

enum SAVESLOT
{
	SAVE_ONE,SAVE_TWO,SAVE_THREE,SAVE_END
};

enum SAVETEXT
{
	NAME, STAT, TIME, SAVETEXT_END
};

struct tagSlot
{
	tagOnlyText textCaption[SAVETEXT_END];
	tagOnlyText text[SAVETEXT_END];
	RECT slotRc;
	Image* newGame;
	Image* face;
	bool isSaved;
};

class Save :public GameNode
{
private:

	// selected Slot 001 010 100 
	bitset<3> _buttonCheck;
	tagSlot _slot[SAVE_END];
	RECT _selectRc;
	RECT _deleteRc;

	float _count;
	bool _nextScene;
	int _chooseIndex;
	tagOnlyText _rScreenMBox;
	tagSceneFadeOut fadeOut;
	tagFingerMouse fingerPointer;

public:
	Save():
	_rScreenMBox{L"사용할 데이터를 선택하세요."}
	{}
	~Save() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void selectSlot();
	void selectMenu(); // next or delete
	
	void playerInfoRender();
};
