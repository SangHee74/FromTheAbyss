#pragma once
#include "SingletonBase.h"
#include "Image.h"


class ImageManager :public SingletonBase <ImageManager>
{
private:
	typedef map <string, Image*> mapImageList;
	typedef map <string, Image*> ::iterator mapImageIter;

private:
	mapImageList _mImageList;


public:
	ImageManager() {}
	~ImageManager() {}

	// 초기화, 해제
	HRESULT init(void);
	void release(void);

	
	// 이미지 추가 
	Image* addImage(string strKey, int width, int height);
	Image* addImage(string strKey, const char* fileName, int width, int height, 
		BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	Image* addImage(string strKey, const char* fileName, float x, float y, int width, int height, 
		BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	
	Image* addFrameImage(string strKey, const char* fileName, int width, int height, int maxFrameX, int maxFrameY, 
		BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	Image* addFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, 
		BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));


	// 이미지 키값으로 찾기
	Image* findImage(string strKey);

	// 이미지 키값으로 삭제
	bool deleteImage(string strKey);

	// 이미지 전체 삭제
	bool deleteAll();


	//=======================================

	// 렌더 / 배경, 플레이어 , 클리핑 순
	void render(string strKey, HDC hdc);
	void render(string strKey, HDC hdc, int destX, int destY);
	void render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	// 알파렌더 / 배경, 플레이어, 클리핑 순
	void alphaRender(string strKey, HDC hdc, BYTE alpha);
	void alphaRender(string strKey, HDC hdc, int destX,int destY, BYTE alpha);
	void alphaRender(string strKey, HDC hdc, int destX, int destY,int sourX,int sourY, int sourWidth, int sourHeight, BYTE alpha);

	// 프레임 렌더
	void frameRender(string strKey, HDC hdc, int destX, int destY);
	void frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);
	
	// 프레임 알파렌더 
	void frameAlphaRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY,BYTE alpha);

	// 루프 렌더 
	void loopRender(string strKey, HDC hdc, const LPRECT dramArea, int offsetX, int offsetY);
	void loopAlphaRender(string strKey, HDC hdc, const LPRECT dramArea, int offsetX, int offsetY, BYTE alpha);



};

