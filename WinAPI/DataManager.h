#pragma once
#include "SingletonBase.h"
#include "Player.h"
#include "Inventory.h"

enum GATE
{
	// ���� , ��������Ʈ, �ӽ� ��� 
	GATE_HOME, GATE_BEFORESTAGE, GATE_NEXTSTAGE,
	GATE_TEMP, GATE_END
};

struct tagGate
{
	RECT drawRc[GATE_END]; // 0����Ȧ, 1������ , 2 �ӽ����
	RECT inRc[GATE_END]; // ���η�Ʈ
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

struct tagEnterStageTextImage
{
	Image* abyssTextImg;
	Image* stageTextImg;
	int alpha;
	float showTime;
};


class DataManager :public SingletonBase<DataManager>
{
private:

	// �÷��̾� ������
	PLAYERNUMBER _playerNumber;
	Player* _player;		 // ���� �÷��̾� ������
	Inventory* _inven;		 // �÷��̾� �κ��丮 ������
	
	// 100 ���� 000 �̼��� , 000Ʃ�丮�� 001 1��� 010 2���
	bitset<3> _storyRewardCheck;  // ���丮 ���� ���� ����(��-Lufia)
	int _storyRewardLufia[3]; // ���丮 ���� �ݾ�



	// ����, �� ������ 
	tagMapSettingData _mapData; // ���, �������� ������ 



public:
	// ���̺� ���Ժ� �̴�
	HRESULT init(PLAYERNUMBER playerNumber);
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	// �÷��̾� ������ ����
	PLAYERNUMBER& getPlayerNumber() { return _playerNumber; }
	Player* getPlayer() { return _player; }
	void setPlayer(Player* User) { _player = User; }
	void clearPlayer() { _player = nullptr; }
	Inventory* getInven() { return _inven; }
	bitset<3> getStoryRewardCheck() { return _storyRewardCheck; }
	int getStoryRewardLufia(int num) {return _storyRewardLufia[num];	}
	
	// �������� �� �� ����
	tagMapSettingData& getMapData() {	return _mapData;	}
	void setStageSetting(void) ; // �������� ����

	// ���ڸ� �̹����� �����ֱ�
	void showNumberImgAlignLeft(int number, POINT rightTopPos);
};


enum EonOff
{
	ON, NEXT, ONOFF_END
};

struct tagSceneFadeOut
{
	int alpha;
	// 00 none, 01 fadeIn , 10 nextScene
	bitset<ONOFF_END> onOff; 
	Image* blackImg;

	void init()
	{
		alpha = 0;
		onOff.reset(); // 00
		blackImg = IMG("black");
	}
	void update()
	{
		if( onOff.test(ON))
		alpha += 2;
		if ( alpha >= 255)
		{
			alpha = 255;
			onOff.flip();
		}
	}
	void reset()
	{
		alpha = 0;
		onOff.reset();
	}
};

struct tagFingerMouse
{
	POINT pos;
	Image* img;
	int speed;
	float reverseTime = 0;
	bool isReturn;
	
	void init()
	{
		pos = {0,0};
		speed = 2;
		reverseTime = 0.0f;
		isReturn = false;
		img = IMG("finger");
	}
	void update()
	{
		//cout << " �հ��� ��ǥ : "<<  pos.x << "," << pos.y << endl;
		reverseTime += TIMEMANAGER->getElapsedTime();
		
		if (isReturn)
		{
			pos.x -= speed; pos.y -= speed;
		}
		else
		{
			pos.x += speed; pos.y += speed;
		}
		
		if (reverseTime >= 0.3) isReturn = true;
		if (reverseTime >= 0.55 && isReturn)
		{
			reverseTime = 0.0f;
			isReturn = false;
			speed = 2;
		}
	}
	void reset()
	{
		pos = { 0,0 };
		speed = 1;
		reverseTime = 0.0f;
		isReturn = false;
		img = IMG("finger");
	}
};

