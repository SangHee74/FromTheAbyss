#pragma once
#include "GameNode.h"

enum MAINSCENE
{
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
	int _selectMenu;
	//int _selectCount;
	bool _isWaitInput;

#pragma region main bit flags
	unsigned char mainIdx;

	unsigned char abyss = 1 << 0;			// 0000 0001 
	unsigned char pub = 1 << 1;				// 0000 0010
	unsigned char store = 1 << 2;			// 0000 0100 
	unsigned char squre = 1 << 3;			// 0000 1000 
	unsigned char tuto = 1 << 4;			// 0001 0000 
	unsigned char castle = 1 << 5;			// 0010 0000 
#pragma endregion

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

	void menuSelect();
	void menuInfo(int textNum);
};

