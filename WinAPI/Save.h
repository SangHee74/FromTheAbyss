#pragma once
#include "GameNode.h"
#define MAXSAVESLOT 3

struct tagSlot
{
	tagOnlyText _txet;
	RECT _slotRc;
	Image* _newGame;
	Image* _newGameSelect;
	bool _isSaved;
	bool _isSelected;
};

class Save :public GameNode
{
private:
	tagSlot _slot[MAXSAVESLOT];
	RECT _selectRc;
	RECT _deleteRc;



	bool _chcekLast;

public:
	Save() {}
	~Save() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};
