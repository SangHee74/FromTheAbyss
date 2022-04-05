#include "Stdafx.h"
#include "Camera.h"

Camera::Camera()
{
    _trace.x = LSCENTER_X;
    _trace.y = CENTER_Y;
    _count = 0;

    _screen = RectMakeCenter(_trace.x, _trace.y, CENTER_X, WINSIZE_Y);
    _leftLimit = LSCENTER_X;
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
	_screen = RectMakeCenter(_trace.x, _trace.y, CENTER_X, WINSIZE_Y);


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