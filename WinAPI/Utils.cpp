#include "Stdafx.h"
#include "Utils.h"

namespace MY_UTIL
{
	float getDistance(float startX, float startY, float endX, float endY)
	{
		float x = endX - startX;
		float y = endY - startY;

		return sqrt(x*x + y * y);
	
	}

	float getAngle(float startX, float startY, float endX, float endY)
	{
		float x = endX - startX;
		float y = endY - startY;
		float d = sqrt(x*x + y * y);
		float angle = acos(x / d);

		if (y > 0)angle = PI_2 - angle;
	
		return angle;
	}


	POINT lerp(POINT start, POINT end, float percentage)
	{
		if (0 > percentage) percentage = 0;
		else if (percentage > 1)percentage = 1;
		LONG x = start.x + (end.x - start.x) * percentage;
		LONG y = start.y + (end.y - start.y) * percentage;
	
		return { x,y };
	}


	
}