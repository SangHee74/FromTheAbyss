#pragma once
//==============================================================
// #Utils# (����ȭ ��Ű�� ���� ����, Ȥ�� ������ ��ɵ��� ��Ƶ� ��)
//==============================================================

// ��׸� 1���� ���� �� (DEG TO RAD)
#define DEG_TO_RAD  0.017453f // 
#define DTR  0.017453f // DEG TO RAD
#define PI   3.141592593f // PI*2 : �Ҽ��� 6�ڸ� �̻��� �ݿø� ������ �����. ��� ������ �� 
#define PI_2 6.283185186f

// ���� + ������ ������

// �ε� �Ҽ��� -> �Ǽ��� ��Ȯ�� ǥ�� �� �� ����.
// �� why? �Ǽ��� ���������� ���� -> ������ �Ǽ��� ������ ��Ʈ�� ǥ���ϴϱ� 
// �� ��ǻ�ʹ� ��¿ �� ���� �ٻ簪���� ó���ع�����.
// �� 2D�� ����� ũ�� �ν��� ��������, 3D ��ǥ�迡�� ���� �ٸ� ����� �߻��Ѵ�.
// �� �ٻ簪�� �� ���� ���� Rounding Error(�ݿø� ����) -> ������ ���� �۽Ƿ� ���� ����� 

#define FLOAT_EPSILON 0.001f

// �Ǽ��� ���������� ��ȯ (FLOAT TO INT)
#define FLOAT_TO_INT(f1)   static_cast<int>(f1+FLOAT_EPSILON)

// �� �Ǽ��� ������ ��
// fabs�� �Ҽ��� ���� ���밪 ��ȯ  // abs -> int 
#define FFLOAT_EQUAL(f1,f2) (fabs(f1-f2) <= FLOAT_EPSILON)
//

namespace MY_UTIL
{
	// �� �� ������ �Ÿ��� ���Ѵ�.
	float getDistance(float startX, float statrY, float endX, float endY);

	//start���� end������ ���� �������� ���Ѵ�.
	float getAngle(float startX, float statrY, float endX, float endY);

}



