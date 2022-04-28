#include "Stdafx.h"
#include "Camera.h"

Camera::Camera()
{
    _trace.x = LSCENTER_X;
    _trace.y = CENTER_Y;
    _count = 0;

    _screen = RectMakeCenter(_trace.x, _trace.y, CENTER_X, WINSIZE_Y);
    _leftLimit = LSCENTER_X;

	_beforeCameraPt = { 0,0 };
	_focusCameraPt = { 0,0 };
	_focusPt = { 0,0 };

	
	// camera shaking
	_shakingOffsetCount = 0;
	_shakingStartTime = 0;
	_shakingTime = 0;
	_isShaking = false;
	_isShakingIncrease = false;

	// camera focusing object
	_focusingOffsetCount = 0;
	_isFocusing = false;
	_isFocusOn = false;

	_focueEventOff = false;

}

HRESULT Camera::init(void)
{
    return S_OK;
}

void Camera::release(void) 
{

}

void Camera::update(void)
{

	// ================================================================================================
    // shaking
    // ================================================================================================
	if (_isShaking)
	{
		_shakingOffsetCount++;
		if (_shakingOffsetCount > 1)
		{
			_shakingOffsetCount = 0;
			_isShakingIncrease = !_isShakingIncrease;
			if (_isShakingIncrease)_trace.y += 4;
			else _trace.y -= 4;
		}

		if (TIMEMANAGER->getWorldTime() > _shakingStartTime + _shakingTime)
		{
			_isShaking = false;
			_shakingStartTime = 0;
			_shakingTime = 0;
			_trace = _beforeCameraPt;
		}
	}



	// ================================================================================================
    // focusing
    // ================================================================================================
	
	if (_isFocusing && !_isFocusOn)
	{
		// 저장한 포커스 위치가 아니면 계속 움직이기 

		if (_focusPt.y >= _focusCameraPt.y + 160)
		{
			_focusPt.y -= 6;

			if (_focusPt.y <= _focusCameraPt.y + 160 )
			{
				// 포커스 위치가 맞음 
				_isFocusOn = true;
			}

		}
	}

	if (_isFocusOn)
	{
		// 지정한 위치면 타임카운트 시작 
		_focusingOffsetCount++;
		if (_focusingOffsetCount > 220) // 원하는 시간만큼 포커싱 했으면 
		{
			_focusingOffsetCount = 0;
			_isFocusing = false;
		}

		if (!_isFocusing )// || _focueEventOff )  
		{
			_focusPt = _beforeCameraPt;
			_isFocusing = false;
			_isFocusOn = false;
			_focueEventOff = false;
		}
	}

	if(_isFocusing)
	{
		_screen = RectMakeCenter(_focusPt.x, _focusPt.y, CENTER_X, WINSIZE_Y);
	}
	else
	{
		_screen = RectMakeCenter(_trace.x, _trace.y, CENTER_X, WINSIZE_Y);
	}

}

void Camera::render(void)
{
}

RECT Camera::getScreenRect()
{
    return _screen;
}

void Camera::setScreenRect(RECT screenRect)
{
    _screen = screenRect;
}

void Camera::setLimitsX(float leftLimit, float rightLimit)
{
#ifdef MapTool
    _leftLimit = leftLimit+155;
    _rightLimit = rightLimit - LSCENTER_X;

#else
	_leftLimit = leftLimit;
	_rightLimit = rightLimit - RSCENTER_X;

#endif // MapTool


}

void Camera::setLimitsY(float topLimit, float bottomLimit)
{
	_topLimit = topLimit;
	_bottomLimit = bottomLimit - CENTER_Y;
}

POINT Camera::getCameraPos()
{
    return _trace;
}

void Camera::setCameraPos(POINT cameraPos)
{
    _trace = cameraPos;
    _trace.x = _trace.x < _leftLimit ? _leftLimit : _trace.x;
    _trace.x = _trace.x > _rightLimit ? _rightLimit : _trace.x;
	_trace.y = _trace.y < _topLimit ? _topLimit : _trace.y;
	_trace.y = _trace.y > _bottomLimit ? _bottomLimit : _trace.y;
}

// 원하는 시간만큼 카메라 추가기능
void Camera::shakeStart(float time)
{
	_shakingStartTime = TIMEMANAGER->getWorldTime();
	_shakingTime = time;
	_beforeCameraPt = _trace;
	_isShaking = true; 
	_isShakingIncrease = true;
}


// focusPt는 중앙에 보이길 원하는 Object의 중점xy
void Camera::focusStart(POINT focusPt)
{
	_beforeCameraPt = _trace;
	_focusCameraPt = focusPt;
	_isFocusing = true;
	_focusPt = _trace;
}

