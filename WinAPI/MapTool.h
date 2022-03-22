#pragma once
#include "GameNode.h"
#include "Tile.h"

struct tagTempTile
{
	float x;
	float y;
};


// 현재 클릭된 타일을 저장
struct tagSampleTile
{
	float x;
	float y;
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
	tagSampleTile _sampleTile;
	tagTilePos _tilePos;

	// 맵툴 편집버튼
	RECT _save; // 현재 어비스와 스테이지 정보로 
	RECT _load; // 저장 또는 로드


	RECT _tileVeuw; // 타일셋 프리뷰 열기닫기

	POINT _pickingPt; // 선택 pt영역(어떤 자리에 타일이 들어갈 지)
	POINT _cameraPtMouse; // 카메라 보정한 마우스좌표

	bool _brushOn; // 스윽-드래그 해서 그리는 상태 온오프
	bool _dragMode; // 드래그 모드 

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
	void tileInit(); // 타일인잇
	void tileRender(); // 타일렌더
	void openCloseBrush(); // 브러쉬 크기 끄기
	void menuInpt(); // 메뉴안에서는 타일 안찍히게
	void dragPaint(); // 드래그 하면서 채우기
	void tempDrag(); // 클릭한 포인트 담기
	void dragOnOff(); // 드래그모드 온오프

	void save();
	void load();
	void imageRender();

	void fill(); // 모든 타일 칠하기 

	void cameraControl();
	
	inline POINT picking(long x, long y); // 피킹하는 함수

	void numberInput();

};


