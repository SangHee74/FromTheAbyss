#pragma once
#include "GameNode.h"
#include "Tile.h"

//Ÿ�� ������
#define TILESIZE_X 26
#define TILESIZE_Y 26

//Ÿ�� ����
#define TILEMAX_X 50
#define TILEMAX_Y 50

//Ÿ�ϼ�(����Ÿ��) ����
#define SAMPLEMAX_X 32
#define SAMPLEMAX_Y 24


// Ÿ�� ��ġ 
struct tagTilePos
{
	float x;
	float y;
};

// Ÿ�ϼ¿��� ������ Ÿ���� ��Ƶ� �� Ÿ��
struct tagTempTile 
{
	abyssType abyssType;
	float x;
	float y;
};

// ������ Ÿ���� ���� �� ���� Ÿ��
// ������ ����.
// ���° ��Ʈ���� �浹�ϴ�����
// 
struct tagSampleTile 
{
	RECT rc;
	float frameX; // �����ӿ��� ���° Ÿ������ 
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

	// ���� ������ư
	RECT _save; // ���� ��񽺿� �������� ������ 
	RECT _load; // ���� �Ǵ� �ε�

	RECT _plusButton[2]; // 0 : abyss, 1:stage
	RECT _minusButton[2];

	RECT _tileView; // Ÿ�ϼ� ������ ����ݱ�
	RECT _wallOn;

	POINT _pickingPt; // ���� pt����(� �ڸ��� Ÿ���� �� ��)
	POINT _cameraPtMouse; // ī�޶� ������ ���콺��ǥ

	bool _brushOn; // ����-�巡�� �ؼ� �׸��� ���� �¿���
	bool _dragMode; // �巡�� ��� 
	bool _tileOn; // Ÿ�� �� ũ�Ⱑ Ŀ��, ���̴���
	bool _isWall;
	bool _guideOn; 
	bitset <1> _guide;

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

	void createTileMap(int tileX, int tileY); // ���̽� Ÿ��
	void createTile();						  // Ÿ�� ������Ʈ 
	void createSampleTile();						  // ���� ������Ʈ 
	void selectSampleTile();

	void tileRender(); // ���õ� Ÿ�� ����

	void openCloseBrush(); // �귯�� ũ�� ����
	void menuInpt(); // �޴��ȿ����� Ÿ�� ��������
	void dragPaint(); // �巡�� �ϸ鼭 ä���
	void tempDrag(); // Ŭ���� ����Ʈ ���
	void dragOnOff(); // �巡�׸�� �¿���

	void save();
	void load();
	void imageRender();
	void infoUpdate();
	void infoRender();
	void sampleRender();

	void fill(); // ��� Ÿ�� ĥ�ϱ� 

	void cameraControl();
	
	inline POINT picking(long x, long y); // ��ŷ�ϴ� �Լ�

	void numberInput();

};


