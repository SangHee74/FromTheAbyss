#pragma once
#include "GameNode.h"

#define INVEN_SIZE 12
#define INVEN_TAP 3

struct tagInvenPos
{
	RECT rc;
	int x;
	int y;
	int slotNum;
};

struct tagCurrentSlot
{
	Image* slot;
	POINT pos;
};


class SubInven : public GameNode
{
private:
	RECT _rc;
	tagCurrentSlot _currentSlot;



	bool _onInvenTile;

public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);



};

