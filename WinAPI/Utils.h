#pragma once
//==============================================================
// #Utils# (간소화 시키고 싶은 로직, 혹은 수학적 기능들을 모아둔 곳)
//==============================================================

// 디그리 1도의 라디안 값 (DEG TO RAD)
#define DEG_TO_RAD  0.017453f // 
#define DTR  0.017453f // DEG TO RAD
#define PI   3.141592593f // PI*2 : 소숫점 6자리 이상은 반올림 오류가 생긴다. 상수 지정할 것 
#define PI_2 6.283185186f

// 공학 + 수학의 구세주

// 부동 소수점 -> 실수를 정확히 표현 할 수 없다.
// ㄴ why? 실수는 수학적으로 무한 -> 무한한 실수를 유한한 비트로 표현하니까 
// ㄴ 컴퓨터는 어쩔 수 없이 근사값으로 처리해버린다.
// ㄴ 2D는 사람이 크게 인식을 못하지만, 3D 좌표계에선 전혀 다른 결과가 발생한다.
// ㄴ 근사값의 주 오류 원인 Rounding Error(반올림 오차) -> 방지를 위해 앱실론 값을 사용함 

#define FLOAT_EPSILON 0.001f

// 실수를 정수형으로 변환 (FLOAT TO INT)
#define FLOAT_TO_INT(f1)   static_cast<int>(f1+FLOAT_EPSILON)

// 두 실수가 같은지 비교
// fabs는 소수점 차의 절대값 반환  // abs -> int 
#define FFLOAT_EQUAL(f1,f2) (fabs(f1-f2) <= FLOAT_EPSILON)
//

namespace MY_UTIL
{
	// 두 점 사이의 거리를 구한다.
	float getDistance(float startX, float statrY, float endX, float endY);

	//start부터 end까지의 각을 라디안으로 구한다.
	float getAngle(float startX, float statrY, float endX, float endY);

}



