#pragma once
#include "SingletonBase.h"
#include "Player.h"

enum GATE
{
	// 마을 , 다음게이트, 임시 통로 
	GATE_HOME, GATE_BEFORESTAGE, GATE_NEXTSTAGE,
	GATE_TEMP, GATE_END
};
struct tagGate
{
	RECT rc[GATE_END]; // 0메인홀, 1다음맵 , 2 임시통로
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

class DataManager :public SingletonBase<DataManager>
{
private:

	// 플레이어 데이터
	PLAYERNUMBER _playerNum; // 세이브용 데이터
	Player* _player;		 // 현재 플레이어 데이터

	// 던전, 맵 데이터 
	tagMapSettingData _mapData; // 어비스, 스테이지 데이터 



public:
	// 세이브 슬롯별 이닛
	HRESULT init(PLAYERNUMBER playerNum);
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	// 플레이어 데이터 관리
	PLAYERNUMBER& getPlayerNumber() { return _playerNum; }
	Player* getPlayer() { return _player; }
	void setPlayer(Player* User) { _player = User; }
	void clearPlayer() { _player = nullptr; }

	// 스테이지 별 맵 관리
	tagMapSettingData& getMapData() {	return _mapData;	}
	void setStageSetting(void) ; // 스테이지 세팅


};

