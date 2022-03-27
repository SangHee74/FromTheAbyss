#include "Stdafx.h"
#include "Camera.h"

Camera::Camera()
{
#ifdef mapTool
	int x = (WINSIZE_X - 320) * 0.5;
	_trace.x = x;
	_trace.y = CENTER_Y;
	_count = 0;
	_screen = RectMakeCenter(_trace.x, _trace.y, WINSIZE_X-320, WINSIZE_Y);
	_leftLimit = x;
#else
    _trace.x = LSCENTER_X;
    _trace.y = CENTER_Y;
    _count = 0;

    _screen = RectMakeCenter(_trace.x, _trace.y, CENTER_X, WINSIZE_Y);
    _leftLimit = LSCENTER_X;
#endif // mapTool
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
#ifdef mapTool
	_screen = RectMakeCenter(_trace.x, _trace.y, WINSIZE_X, WINSIZE_Y);
#else
	_screen = RectMakeCenter(_trace.x, _trace.y, CENTER_X, WINSIZE_Y);
#endif
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
#ifdef mapTool
	_leftLimit = leftLimit;
	_rightLimit = rightLimit - 480;
#else
    _leftLimit = leftLimit;
    _rightLimit = rightLimit - LSCENTER_X;
#endif
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