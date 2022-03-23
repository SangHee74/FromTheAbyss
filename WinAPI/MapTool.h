#pragma once
#include "GameNode.h"
#include "Tile.h"

//타일 사이즈
#define TILESIZE_X 26
#define TILESIZE_Y 26

//타일 갯수
#define TILEMAX_X 50
#define TILEMAX_Y 50

//타일셋(샘플타일) 범위
#define SAMPLEMAX_X 32
#define SAMPLEMAX_Y 24


// 타일 위치 
struct tagTilePos
{
	float x;
	float y;
};

// 타일셋에서 선택한 타일을 담아둘 빈 타일
struct tagTempTile 
{
	abyssType abyssType;
	float x;
	float y;
};

// 선택한 타일이 셋팅 될 샘플 타일
// 우측에 셋팅.
// 몇번째 렉트에서 충돌하는지와
// 
struct tagSampleTile 
{
	RECT rc;
	float frameX; // 프레임에서 몇번째 타일인지 
	float frameY; 
};

class MapTool : public GameNode
{
private:
	Tile _tile[TILEMAX_X*TILEMAX_Y];
	tagTilePos _tilePos;
	tagTempTile _tempTile;
	tagSampleTile _sampleTile[SAMPLEMAX_X*SAMPLEMAX_Y];
	Image* _selectTileView;

	RECT _miniMap;
	RECT _selectTile;
	RECT _tileSlot;

	// 맵툴 편집버튼
	RECT _save; // 현재 어비스와 스테이지 정보로 
	RECT _load; // 저장 또는 로드

	RECT _plusButton[2]; // 0 : abyss, 1:stage
	RECT _minusButton[2];

	RECT _tileView; // 타일셋 프리뷰 열기닫기
	RECT _wallOn;

	POINT _pickingPt; // 선택 pt영역(어떤 자리에 타일이 들어갈 지)
	POINT _cameraPtMouse; // 카메라 보정한 마우스좌표

	bool _brushOn; // 스윽-드래그 해서 그리는 상태 온오프
	bool _dragMode; // 드래그 모드 
	bool _tileOn; // 타일 셋 크기가 커서, 보이는지
	bool _isWall;
	bool _guideOn; 
	bitset <1> _guide;

	int _curAbyss; // 현재 어비스 
	int _curStage;  // 현재 스테이지 

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
	void createSampleTile();						  // 샘플 업데이트 
	void selectSampleTile();

	void tileRender(); // 세팅된 타일 렌더

	void openCloseBrush(); // 브러쉬 크기 끄기
	void menuInpt(); // 메뉴안에서는 타일 안찍히게
	void dragPaint(); // 드래그 하면서 채우기
	void tempDrag(); // 클릭한 포인트 담기
	void dragOnOff(); // 드래그모드 온오프

	void save();
	void load();
	void imageRender();
	void infoUpdate();
	void infoRender();
	void sampleRender();

	void fill(); // 모든 타일 칠하기 

	void cameraControl();
	
	inline POINT picking(long x, long y); // 피킹하는 함수

	void numberInput();

};


