#pragma once
#include "GameNode.h"
#include "Tile.h"

struct tagTempTile
{
	float x;
	float y;
};

struct tagSampleTile
{

};

struct tagTilePos
{
	float x;
	float y;
};


class MapTool : public GameNode
{
private:
	Tile _tile[TILEMAX_X*TILEMAX_Y];
	tagTempTile _tempTile;
	//tagSampleTile _sampleTile;
	tagTilePos _tilePos;

	// 맵툴 편집버튼
	

public:
	MapTool() {}
	~MapTool() {}
};


