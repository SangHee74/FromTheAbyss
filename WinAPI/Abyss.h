#pragma once
#include "GameNode.h"

enum BUTTON_NUM
{
	BUTTON_ONE,
	BUTTON_TWO,
	BUTTON_THREE,
	BUTTON_END
};

class Abyss :public GameNode
{
private:

	tagOnlyText _index[3];		// npc 대화
	
	RECT _buttonRc[BUTTON_END]; // 어비스/스테이지 선택버튼
	RECT _backButton;		    // 뒤로가기
	RECT _upButton;				// 위로 올리기
	RECT _downButton;			// 아래로 내리기 

	bool _mainHall;			    // 메인홀로 돌아가기 
	bool _isWaitDubbleClick;	// 더블클릭 대기
	bool _selectAbyss;			// 처음엔 어비스, 두번째는 스테이지 선택
	BUTTON_NUM  _selectButton; 
	
	tagFingerMouse fingerPointer;
	tagSceneFadeOut fadeOut;

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

	void selectStage();

};