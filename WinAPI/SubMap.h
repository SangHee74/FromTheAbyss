#pragma once
#include "GameNode.h"

// ���-�������� �� �̴ϸ� 
//struct tagMiniMapCheck
//{
//	int _mapRangeX[4];
//	int _mapRangeY[4];
//	bitset<16> mapOpen; // 4*4
//};

struct tagMiniMapImg
{
	RECT miniMapTile;
	Image* miniMapPath;
	int pathFrameX;
	bool OnMiniMapTile;
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
	int _curIndex;

	Image* _returnImg;
	Image* _nextImg;
	Image* _playerPositionImg;
	int _returnNum;
	int _nextNum;
	vector<tagMiniMapImg> _vMiniMap; //
	vector<tagMiniMapImg>::iterator _viMiniMap;

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
	//void minimapRender();
};

