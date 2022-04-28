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

	L"���Ȧ",L"<��� Ȧ> �Դϴ�. �̰����� �Ŵ��� ���� �����ϴ� ������ �̱ÿ� ������ �� �ֽ��ϴ�.",
	L"������ ����",L"<������ ����> �Դϴ�. �ϱ����� ����ϰų� ������, ��ų�� �ñ� �� �ֽ��ϴ�.",
	L"������ ��ȭ��",L"<������ ��ȭ��> �Դϴ�. ���迡 �ʿ��� �������� �����ϰų� ���ʿ��� �������� �Ǹ��մϴ�.",
	L"�̺��� ����",L"<�̺��� ����> �Դϴ�. ���忡 ���� ������� �߿����� �ʿ��� ������ ���� �����...?",
	L"��� �ȳ���",L"<��� �ȳ���> �Դϴ�. ���迡 �ʿ��� ������ �˷��ݴϴ�. ���۹���� �� �𸣰ڴٸ� �����ô�.",
	L"�纥�Ͽ�Ʈ��",L"<�纥�Ͽ�Ʈ��> �Դϴ�. ������ ������ �� �����Ƿ�, ������ ��ġ��� �����Ϸ� ���ô�."
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

