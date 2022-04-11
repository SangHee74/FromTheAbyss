#pragma once
#include "GameNode.h"

// ���-�������� �� �̴ϸ� 
//struct tagMiniMapCheck
//{
//	int _mapRangeX[4];
//	int _mapRangeY[4];
//	bitset<16> mapOpen; // 4*4
//};

struct tagMinimapImg
{
	RECT miniMapTile[16];
	Image* miniMap[16];
	Image* returnImg;
	Image* nextImg;
	Image* playerPositionImg;
};

class SubMap : public GameNode
{
private:

	tagOnlyText _abyssName[2];
	Image* _abyssThumbnail;
	Image* _abyssNum;
	Image* _StageNum;

	int _settingAbyss;
	int _settingStage;

private: // miniMap

	int _mapMaxWidth;
	int _mapMaxHeight;
	int _mapIndexX;
	int _mapIndexY;
	int _mapRangeX[4];
	int _mapRangeY[4];
	bitset<16> _nimiMapOpen; // 4*4
	tagMinimapImg _pathNavigation; // abyss*stage

public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	SubMap(): _abyssName
	{
	L"",
	L"�ʿ��� �ɿ�"//,
	//L"������ �ɿ�",
	//L"���� �ɿ�",
	}
	{}
	~SubMap() {}

	//miniap
	void minimapCheck();
	void minimapRender();
};

