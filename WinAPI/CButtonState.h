#pragma once
#include "GameNode.h"

//typedef void(*CALLBACK_FUNCTION)(void);

// ����Ʈ �����͸� Ȱ���� �ݹ� ���� 
// ���̵� ������ -> ��ư�� �⺻������ 3���� ����

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


