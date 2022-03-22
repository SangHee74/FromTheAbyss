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
	RECT _saveAbyss[4]; 
	RECT _saveStage[4];

	RECT _open;
	RECT _close;

	POINT _pickingPt;
	POINT _cameraPtMouse;

	bool _brushOn;
	bool _menuInpt;
	bool _dragMode;

	int _curAbyss;
	int _curStage; 

public:
	MapTool() {}
	~MapTool() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

public:
	void createTileMap(int tileX, int tileY); // 베이스 타일
	void createTile();						  // 타일 업데이트 
	void tileInit(); // 타일인잇
	void tileRender(); // 타일렌더
	void openCloseBrush(); // 브러쉬 크기 끄기
	void menuInpt(); // 메뉴안에서는 타일 안찍히게
	void dragPaint(); // 드래그 하면서 채우기
	void tempDrag(); // 클릭한 포인트 담기
	void dragOnOff(); // 드래그모드 온오프

	void save();
	void load();

	void fill(); // 모든 타일 칠하기 

	void cameraControl();
	
	inline POINT picking(long x, long y); // 피킹하는 함수

	void numberInput();

};


