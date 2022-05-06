#pragma once

class Animation;


class Image
{
public:

	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE = 0, 
		LOAD_FILE,
		LOAD_EMPTY, 
		LOAD_END
	};

	typedef struct tagImage
	{
		DWORD resID;
		HDC hMemDC; 
		HBITMAP hBit;
		HBITMAP hOBit;
		int x;
		int y;
		int width; 
		int height; 
		int maxFrameX;
		int maxFrameY;
		int currentFrameX;
		int currentFrameY;
		int frameWidth;
		int frameHeight;
		BYTE loadType; 

		tagImage()
		{
			resID = 0;
			hMemDC = NULL;
			hBit=NULL;
			hOBit = NULL;
			x =0;
			y=0;
			width = 0;
			height = 0;
			maxFrameX=0;
			maxFrameY=0;
			currentFrameX=0;
			currentFrameY=0;
			frameWidth=0;
			frameHeight=0;
			loadType = LOAD_RESOURCE;
		}

	}	IMAGE_INFO, *LPIMAGE_INFO; 

private:
	LPIMAGE_INFO _imageInfo; 
	CHAR* _fileName; 
	BOOL _isTrans; 
	COLORREF _transColor;
						 
	BLENDFUNCTION _blendFunc;
	LPIMAGE_INFO _blendImage;

public:
	// 빈 비트맵으로 초기화
	HRESULT init(int width, int height);

	// 이미지 리소스로 초기화
	HRESULT init(const DWORD resID, int width, int height, BOOL isTrans = FALSE,
		COLORREF transColor = RGB(0, 0, 0));

	// 이미지 파일로 초기화
	HRESULT init(const char* fileName, int width, int height, BOOL isTrans = FALSE,
		COLORREF transColor = RGB(0, 0, 0));

	// 프레임 이미지 파일로 초기화
	HRESULT init(const char* fileName, float x, float y,int width, int height, BOOL isTrans = FALSE,
		COLORREF transColor = RGB(0, 0, 0));

	HRESULT init(const char* fileName, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans = FALSE,
		COLORREF transColor = RGB(0, 0, 0));

	HRESULT init(const char* fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans = FALSE,
		COLORREF transColor = RGB(0, 0, 0));


	// 알파블렌드 초기화(추상화)
	HRESULT initForAlphaBlend(void);

	// 투명 컬러키 셋팅(배경색 날릴건지, 어떤색)
	void setTransColor(BOOL isTrans, COLORREF transColor);

	// 해제
	void release(void);

	//=======================================

	// 렌더 / 배경, 플레이어 
	void render(HDC hdc);
	void render(HDC hdc, int destX, int destY);
	// 클리핑 렌더
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	// 알파렌더 / 배경, 플레이어
	void alphaRender(HDC hdc, BYTE alpha);
	void alphaRender(HDC hdc, int destX,int destY, BYTE alpha);
	// 클리핑 알파렌더
	void alphaRender(HDC hdc, int destX, int destY,int sourX,int sourY, int sourWidth, int sourHeight, BYTE alpha);

	// 프레임 렌더
	void frameRender(HDC hdc, int destX, int destY);
	void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	// 루프 렌더 
	void loopRender(HDC hdc, const LPRECT dramArea, int offsetX, int offsetY);
	void loopAlphaRender(HDC hdc, const LPRECT dramArea, int offsetX, int offsetY, BYTE alpha);

	// 0214 에니랜더 추가
	void aniRender(HDC hdc, int destX, int destY, Animation* ani);
	void frameAlphaRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha);


	//=========================
	// 인라인 함수
	//=========================

	// DC 얻기
	inline HDC getMemDC(void) { return _imageInfo->hMemDC; }

	// 이미지 X좌표
	inline float getX(void) { return _imageInfo->x; }
	inline void setX(float x) { _imageInfo->x=x; }

	// 이미지 Y좌표
	inline float getY(void) { return _imageInfo->y; }
	inline void setY(float y) { _imageInfo->y=y; }

	// 이미지 센터좌표
	inline void setCenter(float x, float y)
	{
		_imageInfo->x = x - (_imageInfo->width / 2);
		_imageInfo->y = y - (_imageInfo->height / 2);
	}

	// 이미지 가로세로
	inline int getWidth(void) { return _imageInfo->width; }
	inline int getHeight(void) { return _imageInfo->height; }

	// 바운딩박스(충돌용렉트)
	inline RECT boundingBox(void)
	{
		RECT rc =
		{
		(int)_imageInfo->x,
		(int)_imageInfo->y,
		(int)_imageInfo->x + _imageInfo->width,
		(int)_imageInfo->y + _imageInfo->height
		};
		return rc;
	}

	// 바운딩박스(충돌용렉트)
	inline RECT boundingBoxWithFrame(void)
	{
		RECT rc =
		{
		(int)_imageInfo->x,
		(int)_imageInfo->y,
		(int)_imageInfo->x + _imageInfo->frameWidth,
		(int)_imageInfo->y + _imageInfo->frameHeight
		};
		return rc;
	}

	// 프레임X
	inline int getFrameX(void) { return _imageInfo->currentFrameX; }
	inline void setFrameX(int frameX)
	{
		_imageInfo->currentFrameX = frameX;
		if (frameX > _imageInfo->maxFrameX)
		{
			_imageInfo->currentFrameX = _imageInfo->maxFrameX;
		}
	
	}

	// 프레임Y
	inline int getFrameY(void) { return _imageInfo->currentFrameY; }
	inline void setFrameY(int frameY)
	{
		_imageInfo->currentFrameY = frameY;
		if (frameY > _imageInfo->maxFrameY)
		{
			_imageInfo->currentFrameY = _imageInfo->maxFrameY;
		}
	}

	// 이미지 1 프레임 가로, 세로 크기 
	inline int getFrameWidth(void) { return _imageInfo->frameWidth; }
	inline int getFrameHeight(void) { return _imageInfo->frameHeight; }

	// 최대 프레임 x,y 갯수
	inline int getMaxFrameX(void) { return _imageInfo->maxFrameX; }
	inline int getMaxFrameY(void) { return _imageInfo->maxFrameY; }


	Image();
	~Image() {};
};

