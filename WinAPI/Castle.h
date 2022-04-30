#pragma once
#include "GameNode.h"

#pragma region textMax

#define ABYSS0LAST 12
#define ABYSS1LAST 6
#define ABYSS8LAST 10


struct tagQueenDialogue
{
	tagOnlyText welcomText;
	tagOnlyText abyss0[ABYSS0LAST];
	tagOnlyText abyss1[ABYSS1LAST];
	tagOnlyText abyss8[ABYSS8LAST];
};

#pragma endregion

class Castle :public GameNode
{
private:

	tagQueenDialogue _castleText;
	RECT _messageBox;
	RECT _next;
	int _textIndex; // 현재 text 순서
	int _maxIndex;  // 현재 abyss의 최대 text 

	int _nextCount;
	bool _firstBG;
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
	void storydCheck();
	void storydRender();


	void giveRewardLufia(int value);



};



