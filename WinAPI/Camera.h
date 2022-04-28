#pragma once
#include "SingletonBase.h"

class Camera : public SingletonBase<Camera>
{
private:
    POINT _trace;
    POINT _focusPt;
    RECT _screen;
    int _count;
    float _leftLimit;
    float _rightLimit;
	float _topLimit;
	float _bottomLimit;

	POINT  _beforeCameraPt;
	
	// camera shaking
	int    _shakingOffsetCount;
	float  _shakingStartTime;
	float  _shakingTime;
	bool   _isShaking;
	bool   _isShakingIncrease;

	// camera focusing object
	POINT  _focusCameraPt;
	int    _focusingOffsetCount;
	bool   _isFocusing;
	bool   _isFocusOn;
	bool   _focueEventOff;

public:
	Camera();
	~Camera() {}
	HRESULT init(void);
    void release(void);
    void update(void);
    void render(void);
	

    POINT getCameraPos();
    void setCameraPos(POINT cameraPos);

    RECT getScreenRect();
    void setScreenRect(RECT screenRect);

    void setLimitsX(float leftLimit, float rightLimit);
    void setLimitsY(float topLimit, float bottomLimit);

	void shakeStart(float time);
	void focusStart(POINT focusPt);
	bool setFocusEventOff(bool state) { _focueEventOff = state; }
	bool getFocusOn()				  { return _isFocusOn; }


};

