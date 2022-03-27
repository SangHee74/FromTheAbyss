#pragma once
#include "GameNode.h"
#include "Tile.h"


//타일 사이즈
#define TILESIZE_X 24
#define TILESIZE_Y 24

//타일 갯수
#define TILEMAX_X 10
#define TILEMAX_Y 10
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

// undo 데이터 저장
struct tagTileStage
{
	tagTile tile[TILEMAX_X*TILEMAX_Y];
};

enum INFO
{
	ABYSSRC, STAGERC, INFO_END
};

class MapTool : public GameNode
{
private:

	Tile _tile[TILEMAX_X*TILEMAX_Y];
	//tagTile _tile[TILEMAX_X*TILEMAX_Y];
	vector<tagTile> _vTiles; //
	vector<tagTile>::iterator _viTiles; //

	stack<tagTileStage> _sTile;
	tagTile _undoTile[TILEMAX_X*TILEMAX_Y];

	tagTilePos _tilePos;
	tagTempTile _tempTile;
	tagSampleTile _sampleTile[SAMPLEMAX_X*SAMPLEMAX_Y];
	
	vector<tagTile> _vCurTile; // = TempTile

	Image* _selectTileView;
	Tile _minimapTile[TILEMAX_X*TILEMAX_Y];
	Image* _minimapTileImg;

	int _curAbyss;		  // 현재 어비스 
	int _curStage;		  // 현재 스테이지 

	// 드래그해서 범위타일 그리기 
	int _startTileX, _startTileY;	 
	int _endTileX, _endTileY;
	int _countX, _countY;

	// 카메라
	POINT _curMapSize; // 카메라 리미트용
	POINT _curPos;
	int camLeft;
	int camTop;

#pragma region info 관련
	
	RECT _sampleTileRect;
	RECT _miniMap;
	RECT _selectTile;
	RECT _tileSlot;

	// 맵툴 편집버튼
	RECT _plusButton[INFO_END];		// 어비스, 스테이지
	RECT _minusButton[INFO_END];	// 변경
	RECT _clear;		  // 타일 전체 비우기

	RECT _tileViewButton; // 타일셋 프리뷰 열기닫기
	RECT _wallOnButton;   // 켜져있으면 벽속성 타일로 수정
	RECT _fillAllTile;	  // 모든 타일 채우기

	RECT _save;			  // 현재 어비스와 스테이지 정보로 
	RECT _load;			  // 저장 또는 로드
	RECT _undo;			  // 실행취소

	bool _sampleTileOn;   // 샘플 타일셋 켜져있을 때
	bool _inSampleTile;	  // 샘플 타일을 고르고 있을 때
	bool _guideOn;		  // 각 렉트의 가이드 표시
	bool _wallOn;		  // 타일충돌영역(벽속성타일그리기모드)
	bool _tempTileOn;     // 템프타일에 샘플타일 정보가 있는 상태  

#pragma endregion

	POINT _pickingPt;     // 선택 pt영역(어떤 자리에 타일이 들어갈 지)
	POINT _cameraPtMouse; // 카메라 보정한 마우스좌표

	bool _brushOn;		  // 스윽-드래그 해서 그리는 상태 온오프
	bool _dragMode;		  // 드래그 모드 



public:
	MapTool() {}
	~MapTool() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

public:

	// init()
	void createCameraLimit();				  // 카메라-맵사이즈 업데이트
	void createTileMap();					  // 좌측 베이스 타일 생성
	void createSampleTile();				  // 우측 샘플 타일 생성
	void createMiniMapTile();				  // 우측 미니맵 타일 생성

	// update()
	void selectTile();						  // 베이스 타일 관련 업데이트 
	void selectSampleTile();				  // 샘플 타일 관련 업데이트 
	void infoUpdate();						  // 우측 인포창 업데이트
	void camControl();
	

	// update() - function
	void ptInTileCheck();					 // 바닥 타일에 마우스가 있는지 체크
	void clear();									 // 모든 타일정보 삭제
	void fill(int abyss, int x, int y);				 // 현재 타일로 모든 타일 칠하기 
	void undo();
	void save();
	void load();
	
	void setCurTile(int x, int y) { this->_countX = x; this->_countY = y; }
	void addCurTile(tagTile tile) { _vCurTile.push_back(tile); }
	void clearCurTile() { _vCurTile.clear(); }

	Tile tileDataSave(Tile tileValue);

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

	void numberInput();
	inline POINT picking(long x, long y); // 피킹하는 함수

};


