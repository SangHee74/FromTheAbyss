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

inline POINT rcCenterPos(RECT &rc)
{
	int posX, posY;
	posX = (rc.right - rc.left) *0.5;
	posY = (rc.bottom - rc.top) *0.5;

	return POINT{ posX, posY };
}


// Ÿ�� �ε��� ����
#pragma region tile
inline int getTileIndexWithPos(int tileX, int tileY, int tileSize, POINT pos)
{
	for (int i = 0; i < tileY; ++i)
	{
		for (int j = 0; j < tileX; ++j)
		{
			// ��ǥ�� Ÿ��ũ��� ������ ���� �ε��� ����
			int iCullX = pos.x / tileSize;
			int iCullY = pos.y / tileSize;
			int iIndex = 0;

			iIndex = (i + iCullY) * tileX + (j + iCullX);

			// ����ó��
			if (iIndex >= tileX * tileY) continue;

			return iIndex;
		}
	}
}

inline int getTileIndexWithPos(int tileX, int tileY, int tileSize, int posX, int posY)
{
	for (int i = 0; i < tileY; ++i)
	{
		for (int j = 0; j < tileX; ++j)
		{
			int iCullX = posX / tileSize;
			int iCullY = posY / tileSize;
			int iIndex = 0;

			iIndex = (i + iCullY) * tileX + (j + iCullX);

			if (iIndex >= tileX * tileY) continue;

			return iIndex;
		}
	}
}

inline int getTileIndexWithPos(int tileX, int tileY, int tileXSize, int tileYSize, int posX, int posY)
{
	for (int i = 0; i < tileY; ++i)
	{
		for (int j = 0; j < tileX; ++j)
		{
			int iCullX = posX / tileXSize;
			int iCullY = posY / tileYSize;
			int iIndex = 0;

			iIndex = (i + iCullY) * tileX + (j + iCullX);

			if (iIndex >= tileX * tileY) continue;

			return iIndex;
		}
	}
}
#pragma endregion