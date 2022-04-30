#include "Stdafx.h"
#include "Image.h" 
#include "Animation.h" 


Image::Image() : _imageInfo(NULL)
				,_fileName(NULL)
				,_isTrans(FALSE)
				,_transColor(RGB(0,0,0))
				,_blendImage(NULL)
				
{
}

HRESULT Image::init(int width, int height)
{
	if (_imageInfo != NULL) this->release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_EMPTY;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);//1
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);//2
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	_fileName = NULL;
	_isTrans = FALSE;
	_transColor = RGB(0, 0, 0);

	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT Image::init(const DWORD resID, int width, int height, BOOL isTrans, COLORREF transColor)
{
	if (_imageInfo != NULL) this->release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_RESOURCE; //
	_imageInfo->resID = resID; // 사용할 리소스ID
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadBitmap(_hInstance,MAKEINTRESOURCE(_imageInfo));
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	_fileName = NULL;
	_isTrans = isTrans;
	_transColor = transColor;

	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);
	return S_OK;
}

HRESULT Image::init(const char* fileName, int width, int height, BOOL isTrans, COLORREF transColor)
{
	if (_imageInfo != NULL) this->release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0; 
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName,IMAGE_BITMAP,
		width,height,LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;


	int len = strlen(fileName);
	_fileName = new CHAR[len + 1]; 
	strcpy_s(_fileName, len + 1, fileName);

	_isTrans = isTrans;
	_transColor = transColor;

	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);
	return S_OK;
}


HRESULT Image::init(const char * fileName, float x, float y, int width, int height, BOOL isTrans, COLORREF transColor)
{

	if (_imageInfo != NULL) this->release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;  
	_imageInfo->resID = 0; 
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP,
		width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;
	_imageInfo->height = height;

	int len = strlen(fileName);
	_fileName = new CHAR[len + 1]; 
	strcpy_s(_fileName, len + 1, fileName);

	_isTrans = isTrans;
	_transColor = transColor;

	
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}


	ReleaseDC(_hWnd, hdc);
	return S_OK;
	
}

HRESULT Image::init(const char * fileName, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans, COLORREF transColor)
{
	if (_imageInfo != NULL) this->release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE; 
	_imageInfo->resID = 0; 
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP,
		width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = maxFrameX-1;
	_imageInfo->maxFrameY = maxFrameY-1;
	_imageInfo->frameWidth = width / maxFrameX;
	_imageInfo->frameHeight = height / maxFrameY;

	int len = strlen(fileName);
	_fileName = new CHAR[len + 1]; 
	strcpy_s(_fileName, len + 1, fileName);

	_isTrans = isTrans;
	_transColor = transColor;

	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);
	return S_OK;
}

HRESULT Image::init(const char * fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans, COLORREF transColor)
{
	if (_imageInfo != NULL) this->release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE; 
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP,
		width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = maxFrameX - 1;
	_imageInfo->maxFrameY = maxFrameY - 1;
	_imageInfo->frameWidth = width / maxFrameX;
	_imageInfo->frameHeight = height / maxFrameY;

	int len = strlen(fileName);
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_isTrans = isTrans;
	_transColor = transColor;

	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);
	return S_OK;
}

HRESULT Image::initForAlphaBlend(void)
{

	HDC hdc = GetDC(_hWnd);

	_blendFunc.BlendFlags = 0; // 혼합비율 사용안함
	_blendFunc.AlphaFormat = 0; // 이미지 + 소스 제어 or 이미지 제어 여부
	_blendFunc.BlendOp = AC_SRC_OVER; // 비트맵 이미지 비트 수 24 or 32 사용함
	

	// 이미지 정보 새로 생성 후 초기화
	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_FILE; // 파일로드 
	_blendImage->resID = 0; // 리소스 아이디는 없음
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap	(hdc,_imageInfo->width, _imageInfo->height);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZE_X;
	_blendImage->height = WINSIZE_Y;

	
	ReleaseDC(_hWnd, hdc);
	return S_OK;
}

// 투명 컬러키 셋팅
void Image::setTransColor(BOOL isTrans, COLORREF transColor)
{
	_isTrans = isTrans;
	_transColor = transColor;
}

void Image::release(void) 
{
	if (_imageInfo) 
	{
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);

		SAFE_DELETE(_imageInfo);
		SAFE_DELETE_ARRAY(_fileName);

		_isTrans = FALSE;
		_transColor = RGB(0, 0, 0);
	}


	if (_blendImage)
	{
		SelectObject(_blendImage->hMemDC, _blendImage->hOBit);
		DeleteObject(_blendImage->hBit);
		DeleteDC(_blendImage->hMemDC);
		SAFE_DELETE(_blendImage);
	}
}

void Image::render(HDC hdc)
{
	if (_isTrans)
	{
		
		GdiTransparentBlt 
		(
			hdc,					// 복사할 장소의 DC(화면DC(화면에 보여줄))
			0, 0,					// 복사될 좌표 시작 : X, Y
			_imageInfo->width,		// 복사할 이미지 크기 : 가로, 세로
			_imageInfo->height,
		//------------------------------------------------------------------
			_imageInfo->hMemDC,		// 복사될 대상의 메모리DC
			0,0,					// 복사 시작 지점 : X, Y
			_imageInfo->width,		// 복사 영역 크기 : 가로, 세로 
			_imageInfo->height,
		//------------------------------------------------------------------
			_transColor				// 복사할 때 제외할 색상
		);
	}

	else 
	{
		BitBlt(hdc, 0, 0, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}

}

// 렌더 (내가 설정한 좌표 x,y 에 그려짐)
void Image::render(HDC hdc, int destX, int destY)
{
	if (_isTrans) 
	{
		GdiTransparentBlt 
		(
			hdc,					// 복사할 장소의 DC(화면DC(화면에 보여줄))
			destX, destY,			// 복사될 좌표 시작 : X, Y
			_imageInfo->width,		// 복사할 이미지 크기 : 가로, 세로
			_imageInfo->height,
		//------------------------------------------------------------------
			_imageInfo->hMemDC,		// 복사될 대상의 메모리DC
			0, 0,					// 복사 시작 지점 : X, Y
			_imageInfo->width,		// 복사 영역 크기 : 가로, 세로 
			_imageInfo->height,
		//------------------------------------------------------------------
			_transColor				// 복사할 때 제외할 색상
		);
	}

	else
	{
		BitBlt(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

void Image::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	if (_isTrans) 
	{
		GdiTransparentBlt 
		(
			hdc,					// 복사할 장소의 DC(화면DC(화면에 보여줄))
			destX, destY,			// 복사될 좌표 시작 : X, Y
			sourWidth,				// 복사할 이미지 크기 : 가로, 세로
			sourHeight,
			//------------------------------------------------------------------
			_imageInfo->hMemDC,		// 복사될 대상의 메모리DC
			sourX, sourY,			// 복사 시작 지점 : X, Y
			sourWidth,				// 복사 영역 크기 : 가로, 세로 
			sourHeight,
			//------------------------------------------------------------------
			_transColor				// 복사할 때 제외할 색상
		);
	}

	else
	{
		BitBlt(hdc, destX, destY, sourWidth, sourHeight,
			_imageInfo->hMemDC, sourX, sourY, SRCCOPY);
	}


}

// 알파렌더(배경)
void Image::alphaRender(HDC hdc, BYTE alpha)
{
	if (!_blendImage) initForAlphaBlend();
	
	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans)
	{
		BitBlt
		(
			_blendImage->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			hdc, 0, 0, SRCCOPY);


		GdiTransparentBlt
		(
			_blendImage->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			//------------------
			_imageInfo->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			//------------------
			_transColor
		);

		AlphaBlend
		(
		hdc,
			0,0,
			_imageInfo->width,
			_imageInfo->height,
			_blendImage->hMemDC,
			0,0,
			_imageInfo->width,
			_imageInfo->height,
			_blendFunc 
		);
	}
	else 
	{
		AlphaBlend
		(
			hdc,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_imageInfo->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_blendFunc 
		);
	}
}

void Image::alphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	if (!_blendImage) initForAlphaBlend();

	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans)
	{
		BitBlt
		(
			_blendImage->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			hdc, 
			destX, destY, SRCCOPY
		);


		GdiTransparentBlt
		(
			hdc,
			destX, destY,
			_imageInfo->width,
			_imageInfo->height,
			//------------------
			_imageInfo->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			//------------------
			_transColor
		);

		AlphaBlend
		(
			hdc,
			destX, destY,
			_imageInfo->width,
			_imageInfo->height,
			_blendImage->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_blendFunc 
		);
	}
	else{
		AlphaBlend
		(
			hdc,
			destX, destY,
			_imageInfo->width,
			_imageInfo->height,
			_imageInfo->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_blendFunc);
	}
	
}

void Image::alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
}

void Image::frameRender(HDC hdc, int destX, int destY)
{
	if (_isTrans)
	{
		GdiTransparentBlt
		(
			hdc,						// 복사할 장소의 DC(화면DC(화면에 보여줄))
			destX, destY,				// 복사될 좌표 시작 : X, Y
			_imageInfo->frameWidth,		// 복사할 이미지 크기 : 가로, 세로
			_imageInfo->frameHeight,
			//------------------------------------------------------------------
			_imageInfo->hMemDC,			// 복사될 대상의 메모리DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,			// 복사 시작 지점 : X, Y
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,		// 복사 영역 크기 : 가로, 세로 
			_imageInfo->frameHeight,
			//------------------------------------------------------------------
			_transColor					// 복사할 때 제외할 색상
		);
	}

	else 
	{
		BitBlt(hdc, destX, destY, 
			_imageInfo->frameWidth, 
			_imageInfo->frameHeight,
			_imageInfo->hMemDC, 
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			SRCCOPY);
	}
}

void Image::frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	// 이미지 예외처리
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;
	if (currentFrameX > _imageInfo->maxFrameX)
	{
		_imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}
	if (currentFrameY > _imageInfo->maxFrameY)
	{
		_imageInfo->currentFrameY = _imageInfo->maxFrameY;
	}

	if (_isTrans)
	{
		GdiTransparentBlt
		(
			hdc,					// 복사할 장소의 DC(화면DC(화면에 보여줄))
			destX, destY,			// 복사될 좌표 시작 : X, Y
			_imageInfo->frameWidth,				// 복사할 이미지 크기 : 가로, 세로
			_imageInfo->frameHeight,
			//------------------------------------------------------------------
			_imageInfo->hMemDC,		// 복사될 대상의 메모리DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,			// 복사 시작 지점 : X, Y
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,				// 복사 영역 크기 : 가로, 세로 
			_imageInfo->frameHeight,
			//------------------------------------------------------------------
			_transColor				// 복사할 때 제외할 색상
		);
	}

	else 
	{
		BitBlt(hdc, destX, destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			SRCCOPY);
	}
}

void Image::loopRender(HDC hdc, const LPRECT dramArea, int offsetX, int offsetY)
{
	//offset 값이 음수인 경우 보정 한다.
	if (offsetX < 0)offsetX = _imageInfo->width + (offsetX % _imageInfo->width);
	if (offsetY < 0)offsetY = _imageInfo->height + (offsetY % _imageInfo->height);

	// 그려지는 영역 세팅
	RECT rcSour;
	int sourWidth;
	int sourHeight;

	// 그려지는  DC 영역 (화면크기)
	RECT rcDest;

	// 그려야 할 전체 영역
	int dramAreaX = dramArea->left;
	int dramAreaY = dramArea->top;
	int dramAreaW = dramArea->right - dramArea->left;
	int dramAreaH = dramArea->bottom - dramArea->top;

	// 세로 루프
	for (int y = 0; y < dramAreaH; y += sourHeight)
	{
		// 소스 영역의 높이 계산
		rcSour.top = (y + offsetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;
		sourHeight = rcSour.bottom - rcSour.top;

		// 소스 영역이 그리는 화면을 넘어갔다면(화면밖으로 나갔을때)
		if (y + sourHeight > dramAreaH)
		{
			// 넘어간 그림의 값만큼 올려준다.
			rcSour.bottom -= (y + sourHeight) - dramAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		// 그려지는 영역
		rcDest.top = y + dramAreaY;
		rcDest.bottom = rcDest.top + sourHeight;


		// 가로 루프
		for (int x = 0; x < dramAreaW; x += sourWidth)
		{
			rcSour.left = (x + offsetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;
			sourWidth = rcSour.right - rcSour.left;

			if (x + sourWidth > dramAreaW)
			{
				rcSour.right -= (x + sourWidth) - dramAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			rcDest.left = x + dramAreaX;
			rcDest.right = rcDest.left + sourWidth;

			// 클리핑

			render(hdc, rcDest.left, rcDest.top, rcSour.left, rcSour.top,
				sourWidth, sourHeight);

		}//end of second
		
	}//end of for

}

void Image::loopAlphaRender(HDC hdc, const LPRECT dramaArea, int offsetX, int offsetY, BYTE alpha)
{

		
}



void Image::aniRender(HDC hdc, int destX, int destY, Animation * ani)
{
	render(hdc, destX, destY, ani->getFramePos().x, ani->getFramePos().y,
		ani->getFrameWidth(), ani->getFrameHeight());
}


// 프레임 알파렌더 수정중
void Image::frameAlphaRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha)
{
	// 알파블랜드를 처음 사용하는지 확인
	if (!_blendImage) initForAlphaBlend();

	_blendFunc.SourceConstantAlpha = alpha;

	// 이미지 예외처리
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;
	if (currentFrameX > _imageInfo->maxFrameX)
	{
		_imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}
	if (currentFrameY > _imageInfo->maxFrameY)
	{
		_imageInfo->currentFrameY = _imageInfo->maxFrameY;
	}

	if (_isTrans)
	{
		// 1 출력해야할 DC에 그려져 있는 내용을 블렌드 이미지에 그린다. 
		BitBlt
		(
			_blendImage->hMemDC,
			0, 0,
			_imageInfo->frameWidth,			
			_imageInfo->frameHeight,
			hdc,
			destX, destY, SRCCOPY
		);


		// 2 원본 이미지 배경을 없앤 후 블랜드 이미지에 그린다.
		GdiTransparentBlt
		(
			hdc,
			destX, destY,
			_imageInfo->frameWidth,	
			_imageInfo->frameHeight,
			//------------------
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,		
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,				
			_imageInfo->frameHeight,
			//------------------
			_transColor
		);


		// 3 블렌드 이미지를 화면에 그린다 
		AlphaBlend
		(
			hdc,
			destX, destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight, 
			_blendImage->hMemDC, // 지뢰조심
			0, 0,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight, 
			_blendFunc
		);

	}
	else {
		AlphaBlend
		(
			hdc,
			destX, destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			0, 0,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_blendFunc);
	}
}

