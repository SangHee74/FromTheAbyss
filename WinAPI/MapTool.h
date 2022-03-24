#pragma once
#include "GameNode.h"
#include "Tile.h"

//Ÿ�� ������
#define TILESIZE_X 24
#define TILESIZE_Y 24

//Ÿ�� ����
#define TILEMAX_X 10
#define TILEMAX_Y 10

//Ÿ�ϼ�(����Ÿ��) ����
#define SAMPLEMAX_X 32
#define SAMPLEMAX_Y 24


// Ÿ�� ��ġ (�ȳ���)
struct tagTilePos
{
	float x;
	float y;
};

// Ÿ�ϼ¿��� ������ Ÿ���� ��Ƶ� �� Ÿ��
struct tagTempTile 
{
	abyssType abyssType;
	int x;
	int y;
};

// ������ Ÿ���� ���� �� ���� Ÿ��
// ������ ����.
// ���° ��Ʈ���� �浹�ϴ�����
struct tagSampleTile 
{
	RECT rc;
	int frameX; // �����ӿ��� ���° Ÿ������ 
	int frameY;
};

enum a {
	abyss, stage,a_end
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

	//�׽�Ʈ�� �����̺���
	bool _isOpenTileList;
	// ���� ������ư
	RECT _save; // ���� ��񽺿� �������� ������ 
	RECT _load; // ���� �Ǵ� �ε�

	RECT _plusButton[a_end]; // 0 : abyss, 1:stage
	RECT _minusButton[a_end];

	RECT _tileViewButton; // Ÿ�ϼ� ������ ����ݱ�
	RECT _wallOnButton; // ���������� ���Ӽ� Ÿ�Ϸ� ����

	POINT _pickingPt;     // ���� pt����(� �ڸ��� Ÿ���� �� ��)
	POINT _cameraPtMouse; // ī�޶� ������ ���콺��ǥ

	bool _brushOn;  // ����-�巡�� �ؼ� �׸��� ���� �¿���
	bool _dragMode; // �巡�� ��� 
	
	bool _sampleTileOn;   // ���� Ÿ�ϼ� �������� ��
	bool _guideOn;  //
	bool _wallOn;
	bool _tempTileOn; // ����Ÿ�Ͽ� ����Ÿ�� ������ �ִ� ����  

	int _curAbyss; // ���� ��� 
	int _curStage;  // ���� �������� 

public:
	MapTool() {}
	~MapTool() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

public:
	
	// init()
	void createTileMap(int tileX, int tileY); // ���̽� Ÿ�� ����
	void createSampleTile();				  // ���� Ÿ�� ����
	
	// update()
	void selectTile();						  // ���̽� Ÿ�� ���� ������Ʈ 
	void selectSampleTile();				  // ���� Ÿ�� ���� ������Ʈ 
	void infoUpdate();						  // ���� ����â ������Ʈ


	// update() - function
	void tilePosCheck();
	void fill(int x, int y); // ���� Ÿ�Ϸ� ��� Ÿ�� ĥ�ϱ� 
	void save();
	void load();


	// render()
	void tileRender();						 // ���̽� Ÿ�� ����
	void imageRender();		
	void infoRender();		 // ���� ��ư ��ġ �� ����
	void sampleTileRender(); // infoRender �� ����Ÿ�ϼ� ����

	// ����~~~~~~
	void openCloseBrush(); // �귯�� ũ�� ����
	void menuInpt();	   // �޴��ȿ����� Ÿ�� ��������
	void dragPaint();      // �巡�� �ϸ鼭 ä���
	void tempDrag();       // Ŭ���� ����Ʈ ���
	void dragOnOff();      // �巡�׸�� �¿���

	void cameraControl();
	void numberInput();
	inline POINT picking(long x, long y); // ��ŷ�ϴ� �Լ�

};


