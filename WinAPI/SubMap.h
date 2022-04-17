#pragma once
#include "GameNode.h"

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
	int _curPathFrameX;

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
	L"초원의 심연"//,
	//L"암굴의 심연",
	//L"고성의 심연",
	}
	{}
	~SubMap() {}

	//miniap
	void minimapCheck();
	int getCurrentIndex()  { return _curIndex; }
	int getRetrunIndex()   { return _returnNum; }
	int getNextIndex()	   { return _nextNum; }
	int getCurPathFrameX() { return _curPathFrameX; }


};

