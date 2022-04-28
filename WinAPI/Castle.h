#pragma once
#include "GameNode.h"

#pragma region textNumberList
#define ABYSS0LAST 12
#define ABYSS1LAST 5
#define ABYSS8LAST 10


#pragma endregion

struct tagQueenDialogue
{
	tagOnlyText welcomText;
	tagOnlyText abyss0[ABYSS0LAST];
	tagOnlyText abyss1[ABYSS1LAST];
	tagOnlyText abyss8[ABYSS8LAST];
};

class Castle :public GameNode
{
private:

	tagQueenDialogue _castleText;
	RECT _messageBox;
	RECT _next;
	int _textIndex; // ���� text ����
	int _maxIndex;  // ���� abyss�� �ִ� text 

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
	void giveRewardLufia(int value);



};



