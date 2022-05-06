#pragma once
#include "GameNode.h"

/*

Debug x86


맵툴 확인시 PCH에서 창모드 -> 맵툴모드로 전환

---

F2 : 픽셀충돌, 플레이어 피격범위, 타격범위 토글
F3 : 몬스터 인식범위, 피격범위, 타격범위 토글

--- 무기 별 대기 모션 확인 
1 : 플레이어 검 착용
2 : 플레이어 도끼 착용
3 : 플레이어 창 착용 

*/


class MainGame :public GameNode
{
	
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);


	MainGame() {}
	~MainGame() {}


};

