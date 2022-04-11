#pragma once
//===========================================================
// # commomMacroFunction # (�ʿ��� �Լ��� ���� ����� �߰�����)
//===========================================================

inline POINT PointMake(int x, int y)
{
	POINT pt = { x, y };
	return pt;
}

inline void LineMake(HDC hdc, int startX, int startY, int endX, int endY)
{
	MoveToEx(hdc, startX, startY, NULL);
	LineTo(hdc, endX, endY);
}

inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x, y, x + width, y + height };
	return rc;
}

inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x - width / 2, y - height / 2, x + width / 2, y + height / 2 };
	return rc;
}

inline void RectangleMake(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}

inline void rcMake(HDC hdc, RECT &rc) 
{
	Rectangle(hdc, rc.left,rc.top,rc.right,rc.bottom);
}

inline void EllipseMake(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}

inline void EllipseMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x - width / 2, y - height / 2, x + width / 2, y + height / 2);
}


// �浹 ���� ������ - ���� �ǰ� ������ ��Ʈ�� W,H �Է� �� �¿�.���Ͽ��� ����
inline RECT CollisionAreaResizing(RECT &rcDest, int width, int height)
{
	RECT rc = { rcDest.left + width / 2, rcDest.top + height / 2,
				rcDest.right - width / 2 ,rcDest.bottom - height / 2 };

	return rc;
}

inline POINT rcMiddlePos(RECT &rc)
{
	int posX, posY;
	posX = (rc.right - rc.left) *0.5;
	posY = (rc.bottom - rc.top) *0.5;

	return POINT{ posX, posY };
}