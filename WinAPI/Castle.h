#pragma once
#include "GameNode.h"

#pragma region textNumberList
#define ABYSS0LAST 10
#define ABYSS1LAST 10
#define ABYSS8LAST 10


#pragma endregion

struct tagQueenDialogue
{
	tagOnlyText abyss0Text[ABYSS0LAST];
	tagOnlyText abyss1Text[ABYSS1LAST];
	tagOnlyText abyss8Text[ABYSS8LAST];
};

class Castle :public GameNode
{
private:

	tagQueenDialogue _castleText;
	RECT _next;
	int _textIndex;
	bool _isQueenSmile; 


public:
	Castle();
	~Castle() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void queenSmileCheck();
	void showDialogue(int index);
	void giveRewardLufia(int value);
};
