#pragma once
#include "GameNode.h"

enum BUTTONNUM
{
	BUTTON_ONE,
	BUTTON_TWO,
	BUTTON_THREE,
	BUTTON_END
};

class Abyss :public GameNode
{
private:

	
	RECT _buttonRc[BUTTON_END]; // 어비스/스테이지 선택버튼
	RECT _backButton;		    // 뒤로가기
	RECT _upButton;				// 위로 올리기
	RECT _downButton;			// 아래로 내리기 
	bool _isWaitInput;			// 더블클릭 대기
	tagOnlyText _index[3];		// npc 대화

	int _abyss;	        // 데이터 매니저로 전달할 던전 정보 
	int _stage;	        // 데이터 매니저로 전달할 던전 정보 
	int _alpha;			// 페이드아웃 알파
	bitset<2> _fadeOut; // 페이드아웃 온오프
	bool _downButtonOn; // 내리기 버튼 활성화 유무 


public:
	Abyss():
		_index
	{ 
		L"너로군.",
		L"오늘은 어떤 세계에 도전할거야?",
		L""
	}
	{}
	~Abyss() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

};