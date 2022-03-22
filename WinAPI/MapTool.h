#pragma once
#include "GameNode.h"
#include "Tile.h"

struct tagTempTile
{
	float x;
	float y;
};


// ���� Ŭ���� Ÿ���� ����
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

	// ���� ������ư
	RECT _save; // ���� ��񽺿� �������� ������ 
	RECT _load; // ���� �Ǵ� �ε�


	RECT _tileVeuw; // Ÿ�ϼ� ������ ����ݱ�

	POINT _pickingPt; // ���� pt����(� �ڸ��� Ÿ���� �� ��)
	POINT _cameraPtMouse; // ī�޶� ������ ���콺��ǥ

	bool _brushOn; // ����-�巡�� �ؼ� �׸��� ���� �¿���
	bool _dragMode; // �巡�� ��� 

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
	void tileInit(); // Ÿ������
	void tileRender(); // Ÿ�Ϸ���
	void openCloseBrush(); // �귯�� ũ�� ����
	void menuInpt(); // �޴��ȿ����� Ÿ�� ��������
	void dragPaint(); // �巡�� �ϸ鼭 ä���
	void tempDrag(); // Ŭ���� ����Ʈ ���
	void dragOnOff(); // �巡�׸�� �¿���

	void save();
	void load();
	void imageRender();

	void fill(); // ��� Ÿ�� ĥ�ϱ� 

	void cameraControl();
	
	inline POINT picking(long x, long y); // ��ŷ�ϴ� �Լ�

	void numberInput();

};


