#pragma once
#include "GameNode.h"

#define INVEN_SIZE_X 4
#define INVEN_SIZE_Y 3
#define INVEN_TAP 3

struct tagInvenPos
{
	RECT rc;
	POINT pos;
	int slotNum;
};

struct tagCurrentSlot
{
	Image* slot;
	RECT rc;
	POINT pos;
};

class SubInven : public GameNode
{
private:
	tagInvenPos _invenPos[INVEN_SIZE_X*INVEN_SIZE_Y];
	tagCurrentSlot _currentSlot;
	RECT _baseRc;


	bool _onInvenTile;

public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void setCurrentSlot(int num);



};

