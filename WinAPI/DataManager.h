#pragma once
#include "SingletonBase.h"
#include "Player.h"

enum GATE
{
	// ���� , ��������Ʈ, �ӽ� ��� 
	GATE_HOME, GATE_BEFORESTAGE, GATE_NEXTSTAGE,
	GATE_TEMP, GATE_END
};
struct tagGate
{
	RECT rc[GATE_END]; // 0����Ȧ, 1������ , 2 �ӽ����
	int inGateCount; // �����ð� �̻� ��� �� ��ü����
};

struct tagMapSettingData
{
	tagAbyssData enterAbyssInfo; // ���, ��������
	tagGate gate; // 0 �Ա�, 1 �ⱸ , 2 �ӽ����
	Image*  map;
	Image*  mapObject;
	Image*  mapTop;
	Image*  pixelMap;
};

class DataManager :public SingletonBase<DataManager>
{
private:

	// �÷��̾� ������
	PLAYERNUMBER _playerNum; // ���̺�� ������
	Player* _player;		 // ���� �÷��̾� ������

	// ����, �� ������ 
	tagMapSettingData _mapData; // ���, �������� ������ 



public:
	// ���̺� ���Ժ� �̴�
	HRESULT init(PLAYERNUMBER playerNum);
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	// �÷��̾� ������ ����
	PLAYERNUMBER& getPlayerNumber() { return _playerNum; }
	Player* getPlayer() { return _player; }
	void setPlayer(Player* User) { _player = User; }
	void clearPlayer() { _player = nullptr; }

	// �������� �� �� ����
	tagMapSettingData& getMapData() {	return _mapData;	}
	void setStageSetting(void) ; // �������� ����


};

