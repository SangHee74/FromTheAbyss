#pragma once
//==============================================================
// #Utils#
//==============================================================

// ��׸� 1���� ���� �� (DEG TO RAD)
#define DEG_TO_RAD  0.017453f // 
#define DTR  0.017453f	  // DEG TO RAD
#define PI   3.141592593f 
#define PI_2 6.283185186f





#define FLOAT_EPSILON 0.001f

// �Ǽ��� ���������� ��ȯ (FLOAT TO INT)
#define FLOAT_TO_INT(f1)   static_cast<int>(f1+FLOAT_EPSILON)

// �� �Ǽ��� ������ ��
#define FFLOAT_EQUAL(f1,f2) (fabs(f1-f2) <= FLOAT_EPSILON)


namespace MY_UTIL
{
	float getDistance(float startX, float statrY, float endX, float endY);

	// start���� end������ ���� �������� ���Ѵ�.
	float getAngle(float startX, float statrY, float endX, float endY);

	// ��������
	POINT lerp(POINT start, POINT end, float percentage);



}



