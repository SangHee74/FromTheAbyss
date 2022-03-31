#pragma once
#include "GameNode.h"

//typedef void(*CALLBACK_FUNCTION)(void);

// 보이트 포인터를 활용한 콜백 구조 
// 보이드 포인터 -> 버튼은 기본적으로 3가지 상태

enum BUTTON_DIRECTION
{
	BUTTON_DIRECTION_NULL,
	BUTTON_DIRECTION_UP,
	BUTTON_DIRECTION_DOWN
};

class CButtonState :public GameNode
{

private:
	BUTTON_DIRECTION _direction;
	Image* _image;

	//RECT _rc;
	//float _x, _y;
	//const char* _imageName;
	//
	//POINT _btnDownFramePoint;
	//POINT _btnUpFramePoint;
//	CALLBACK_FUNCTION _callBackFunction;

public:
//	CButtonState()
//		:_callBackFunction(nullptr)
//	{}
//	~CButtonState() {}
//	
//	HRESULT init(const char* imageName,int x, int y,
//		POINT btnDownFramePoint, POINT btnUpFramePoint);
//	HRESULT init(const char* imageName, int x, int y,
//		POINT btnDownFramePoint, POINT btnUpFramePoint,
//		CALLBACK_FUNCTION cbFunction);
//
//	void release(void);
//	void update(void);
//	void render(void);

};


