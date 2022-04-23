#pragma once
#include "SingletonBase.h"
#include "Player.h"
#include "Inventory.h"

enum GATE
{
	// 마을 , 다음게이트, 임시 통로 
	GATE_HOME, GATE_BEFORESTAGE, GATE_NEXTSTAGE,
	GATE_TEMP, GATE_END
};

struct tagGate
{
	RECT drawRc[GATE_END]; // 0메인홀, 1다음맵 , 2 임시통로
	RECT inRc[GATE_END]; // 내부렉트
	int inGateCount; // 일정시간 이상 경과 시 씬체인지
};

struct tagMapSettingData
{
	tagAbyssData enterAbyssInfo; // 어비스, 스테이지
	tagGate gate; // 0 입구, 1 출구 , 2 임시통로
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

	// 플레이어 데이터
	PLAYERNUMBER _playerNumber;
	Player* _player;		 // 현재 플레이어 데이터
	Inventory* _inven;		 // 플레이어 인벤토리 데이터
	
	// 100 수령 000 미수령 , 000튜토리얼 001 1어비스 010 2어비스
	bitset<3> _storyRewardCheck;  // 스토리 보상 수령 여부(성-Lufia)
	int _storyRewardLufia[3]; // 스토리 보상 금액



	// 던전, 맵 데이터 
	tagMapSettingData _mapData; // 어비스, 스테이지 데이터 



public:
	// 세이브 슬롯별 이닛
	HRESULT init(PLAYERNUMBER playerNumber);
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	// 플레이어 데이터 관리
	PLAYERNUMBER& getPlayerNumber() { return _playerNumber; }
	Player* getPlayer() { return _player; }
	void setPlayer(Player* User) { _player = User; }
	void clearPlayer() { _player = nullptr; }
	Inventory* getInven() { return _inven; }
	bitset<3> getStoryRewardCheck() { return _storyRewardCheck; }
	int getStoryRewardLufia(int num) {return _storyRewardLufia[num];	}
	
	// 스테이지 별 맵 관리
	tagMapSettingData& getMapData() {	return _mapData;	}
	void setStageSetting(void) ; // 스테이지 세팅

	// 숫자를 이미지로 보여주기
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
		//cout << " 손가락 좌표 : "<<  pos.x << "," << pos.y << endl;
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

