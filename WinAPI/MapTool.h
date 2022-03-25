#pragma once
#include "GameNode.h"
#include "Tile.h"

//타일 사이즈
#define TILESIZE_X 24
#define TILESIZE_Y 24
#define SAMPLETILESIZE_X 24
#define SAMPLETILESIZE_Y 24

//타일 갯수
#define TILEMAX_X 20
#define TILEMAX_Y 20
#define SAMPLEMAX_X 32
#define SAMPLEMAX_Y 24


// 타일셋에서 선택한 샘플 타일
struct tagSampleTile
{
	RECT rc;
	int frameX; // 타일셋 이미지에서 몇번째 타일인지 
	int frameY;
};

// 샘플타일을 담아둘 빈 타일
struct tagTempTile 
{
	abyssType abyssType;
	int x;
	int y;
};

// 타일 위치 (안내용)
struct tagTilePos
{
	int x;
	int y;
};

enum INFO
{
	ABYSSRC, STAGERC,INFO_END
};

class MapTool : public GameNode
{
private:

	Tile _tile[TILEMAX_X*TILEMAX_Y];
	vector<Tile> _vTile;
	vector<Tile>::iterator _viTile;

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

	RECT _plusButton[INFO_END];
	RECT _minusButton[INFO_END];

	RECT _tileViewButton; // 타일셋 프리뷰 열기닫기
	RECT _wallOnButton;   // 켜져있으면 벽속성 타일로 수정

	RECT _fillAllTile;	  // 모든 타일 채우기
	RECT _undo;			  // 실행취소


	POINT _pickingPt;     // 선택 pt영역(어떤 자리에 타일이 들어갈 지)
	POINT _cameraPtMouse; // 카메라 보정한 마우스좌표

	bool _brushOn;		  // 스윽-드래그 해서 그리는 상태 온오프
	bool _dragMode;		  // 드래그 모드 
	
	bool _sampleTileOn;   // 샘플 타일셋 켜져있을 때
	bool _inSampleTile;	  // 샘플 타일을 고르고 있을 때
	bool _guideOn;		  // 각 렉트의 가이드 표시
	bool _wallOn;		  // 타일충돌영역(벽속성타일그리기모드)
	bool _tempTileOn;     // 템프타일에 샘플타일 정보가 있는 상태  

	int _curAbyss;		  // 현재 어비스 
	int _curStage;		  // 현재 스테이지 

public:
	MapTool() {}
	~MapTool() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

public:
	
	// init()
	void createTileMap(int tileX, int tileY); // 좌측 베이스 타일 생성
	void createSampleTile();				  // 우측 샘플 타일 생성
	
	// update()
	void selectTile();						  // 베이스 타일 관련 업데이트 
	void selectSampleTile();				  // 샘플 타일 관련 업데이트 
	void infoUpdate();						  // 우측 인포창 업데이트


	// update() - function
	void ptInTileCheck();					 // 바닥 타일에 마우스가 있는지 체크
	void fill(int x, int y);				 // 현재 타일로 모든 타일 칠하기 
	void save();
	void load();


	// render()
	void tileRender();						 // 베이스 타일 렌더
	void imageRender();		
	void infoRender();		 // 맵툴 버튼 위치 등 인포
	void sampleTileRender(); // infoRender 내 샘플타일셋 렌더

	// 아직~~~~~~
	void openCloseBrush(); // 브러쉬 켜기 끄기
	void menuInpt();	   // 메뉴안에서는 타일 안찍히게
	void dragPaint();      // 드래그 하면서 채우기
	void tempDrag();       // 클릭한 포인트 담기
	void dragOnOff();      // 드래그모드 온오프

	void cameraControl();
	void numberInput();
	inline POINT picking(long x, long y); // 피킹하는 함수

};


