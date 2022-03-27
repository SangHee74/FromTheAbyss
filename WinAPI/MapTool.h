#pragma once
#include "GameNode.h"
#include "Tile.h"


//Ÿ�� ������
#define TILESIZE_X 24
#define TILESIZE_Y 24

//Ÿ�� ����
#define TILEMAX_X 10
#define TILEMAX_Y 10
#define SAMPLEMAX_X 32
#define SAMPLEMAX_Y 24


// Ÿ�ϼ¿��� ������ ���� Ÿ��
struct tagSampleTile
{
	RECT rc;
	int frameX; // Ÿ�ϼ� �̹������� ���° Ÿ������ 
	int frameY;
};

// ����Ÿ���� ��Ƶ� �� Ÿ��
struct tagTempTile
{
	abyssType abyssType;
	int x;
	int y;
};

// Ÿ�� ��ġ (�ȳ���)
struct tagTilePos
{
	int x;
	int y;
};

// undo ������ ����
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

	int _curAbyss;		  // ���� ��� 
	int _curStage;		  // ���� �������� 

	// �巡���ؼ� ����Ÿ�� �׸��� 
	int _startTileX, _startTileY;	 
	int _endTileX, _endTileY;
	int _countX, _countY;

	// ī�޶�
	POINT _curMapSize; // ī�޶� ����Ʈ��
	POINT _curPos;
	int camLeft;
	int camTop;

#pragma region info ����
	
	RECT _sampleTileRect;
	RECT _miniMap;
	RECT _selectTile;
	RECT _tileSlot;

	// ���� ������ư
	RECT _plusButton[INFO_END];		// ���, ��������
	RECT _minusButton[INFO_END];	// ����
	RECT _clear;		  // Ÿ�� ��ü ����

	RECT _tileViewButton; // Ÿ�ϼ� ������ ����ݱ�
	RECT _wallOnButton;   // ���������� ���Ӽ� Ÿ�Ϸ� ����
	RECT _fillAllTile;	  // ��� Ÿ�� ä���

	RECT _save;			  // ���� ��񽺿� �������� ������ 
	RECT _load;			  // ���� �Ǵ� �ε�
	RECT _undo;			  // �������

	bool _sampleTileOn;   // ���� Ÿ�ϼ� �������� ��
	bool _inSampleTile;	  // ���� Ÿ���� ���� ���� ��
	bool _guideOn;		  // �� ��Ʈ�� ���̵� ǥ��
	bool _wallOn;		  // Ÿ���浹����(���Ӽ�Ÿ�ϱ׸�����)
	bool _tempTileOn;     // ����Ÿ�Ͽ� ����Ÿ�� ������ �ִ� ����  

#pragma endregion

	POINT _pickingPt;     // ���� pt����(� �ڸ��� Ÿ���� �� ��)
	POINT _cameraPtMouse; // ī�޶� ������ ���콺��ǥ

	bool _brushOn;		  // ����-�巡�� �ؼ� �׸��� ���� �¿���
	bool _dragMode;		  // �巡�� ��� 



public:
	MapTool() {}
	~MapTool() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

public:

	// init()
	void createCameraLimit();				  // ī�޶�-�ʻ����� ������Ʈ
	void createTileMap();					  // ���� ���̽� Ÿ�� ����
	void createSampleTile();				  // ���� ���� Ÿ�� ����
	void createMiniMapTile();				  // ���� �̴ϸ� Ÿ�� ����

	// update()
	void selectTile();						  // ���̽� Ÿ�� ���� ������Ʈ 
	void selectSampleTile();				  // ���� Ÿ�� ���� ������Ʈ 
	void infoUpdate();						  // ���� ����â ������Ʈ
	void camControl();
	

	// update() - function
	void ptInTileCheck();					 // �ٴ� Ÿ�Ͽ� ���콺�� �ִ��� üũ
	void clear();									 // ��� Ÿ������ ����
	void fill(int abyss, int x, int y);				 // ���� Ÿ�Ϸ� ��� Ÿ�� ĥ�ϱ� 
	void undo();
	void save();
	void load();
	
	void setCurTile(int x, int y) { this->_countX = x; this->_countY = y; }
	void addCurTile(tagTile tile) { _vCurTile.push_back(tile); }
	void clearCurTile() { _vCurTile.clear(); }

	Tile tileDataSave(Tile tileValue);

	// render()
	void tileRender();						 // ���̽� Ÿ�� ����
	void imageRender();
	void infoRender();		 // ���� ��ư ��ġ �� ����
	void sampleTileRender(); // infoRender �� ����Ÿ�ϼ� ����

	// ����~~~~~~
	void openCloseBrush(); // �귯�� �ѱ� ����
	void menuInpt();	   // �޴��ȿ����� Ÿ�� ��������
	void dragPaint();      // �巡�� �ϸ鼭 ä���
	void tempDrag();       // Ŭ���� ����Ʈ ���
	void dragOnOff();      // �巡�׸�� �¿���

	void numberInput();
	inline POINT picking(long x, long y); // ��ŷ�ϴ� �Լ�

};


