#pragma once
//==============================================================
// #Utils#
//==============================================================

// 디그리 1도의 라디안 값 (DEG TO RAD)
#define DEG_TO_RAD  0.017453f // 
#define DTR  0.017453f	  // DEG TO RAD
#define PI   3.141592593f 
#define PI_2 6.283185186f





#define FLOAT_EPSILON 0.001f

// 실수를 정수형으로 변환 (FLOAT TO INT)
#define FLOAT_TO_INT(f1)   static_cast<int>(f1+FLOAT_EPSILON)

// 두 실수가 같은지 비교
#define FFLOAT_EQUAL(f1,f2) (fabs(f1-f2) <= FLOAT_EPSILON)


namespace MY_UTIL
{
	float getDistance(float startX, float statrY, float endX, float endY);

	// start부터 end까지의 각을 라디안으로 구한다.
	float getAngle(float startX, float statrY, float endX, float endY);

	// 선형보간
	POINT lerp(POINT start, POINT end, float percentage);



}



