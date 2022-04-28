#pragma once
#include "GameNode.h"

enum MAINSCENE
{
	//MAINSCENE_NONE,
	MAINSCENE_ABYSS, MAINSCENE_PUB,   MAINSCENE_STORE, 
	MAINSCENE_SQURE, MAINSCENE_TUTO,  MAINSCENE_CASTLE, 
	MAINSCENE_END
};

class MainHall:public GameNode
{
private:

	RECT _icon[MAINSCENE_END];
	tagText _menuInfoText[MAINSCENE_END];
	int _textNum;

	// selected menu (fingerMouse)
	// 000001 abyss / 000010 pub / 000100 store 
	// 001000 tuto / 010000 squre/  100000 castle
	//bitset<6> _buttonCheck;
	int _sceneIndex;
	//int _chooseIndex;
	int _changeIndex;

	float _timeCount;
	bool _selectLimit;

	tagFingerMouse fingerPointer;
	tagSceneFadeOut fadeOut;

public:
	MainHall() :
		_menuInfoText
	{

	L"어비스홀",L"<어비스 홀> 입니다. 이곳에서 거대한 마가 존재하는 차원의 미궁에 도전할 수 있습니다.",
	L"모험자 숙소",L"<모험자 숙소> 입니다. 일기장을 기록하거나 아이템, 스킬을 맡길 수 있습니다.",
	L"웰메의 잡화점",L"<웰메의 잡화점> 입니다. 모험에 필요한 아이템을 구입하거나 불필요한 아이템을 판매합니다.",
	L"팟벨른 광장",L"<팟벨른 광장> 입니다. 광장에 모인 마을사람 중에서는 필요한 정보를 가진 사람도...?",
	L"어비스 안내소",L"<어비스 안내소> 입니다. 모험에 필요한 지식을 알려줍니다. 조작방법을 잘 모르겠다면 가봅시다.",
	L"루벤하우트성",L"<루벤하우트성> 입니다. 여왕을 알현할 수 있으므로, 마물을 해치우면 보고하러 갑시다."
	}
	{}
	~MainHall() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void selectSlot();
	void selectMenue();
	void menuInfo(int textNum);
};

