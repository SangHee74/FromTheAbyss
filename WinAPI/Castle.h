#pragma once
#include "GameNode.h"

#pragma region textNumberList
#define ABYSS0LAST 11
#define ABYSS1LAST 10
#define ABYSS8LAST 10


#pragma endregion

struct tagQueenDialogue
{
	tagOnlyText abyss0[ABYSS0LAST];
	tagOnlyText abyss1[ABYSS1LAST];
	tagOnlyText abyss8[ABYSS8LAST];
};

class Castle :public GameNode
{
private:

	tagQueenDialogue _castleText;
	RECT _next;
	int _textIndex;
	int _maxIndex;
	bool _isQueenSmile; 

	tagSceneFadeOut fadeOut;

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
