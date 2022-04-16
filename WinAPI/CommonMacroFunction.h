#pragma once
//===========================================================
// # commomMacroFunction # (필요한 함수는 직접 만들어 추가하자)
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


// 충돌 범위 재조정 - 실제 피격 범위의 렉트의 W,H 입력 시 좌우.상하여백 조정
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


// 타일 인덱스 접근
#pragma region tile
inline int getTileIndexWithPos(int tileX, int tileY, int tileSize, POINT pos)
{
	for (int i = 0; i < tileY; ++i)
	{
		for (int j = 0; j < tileX; ++j)
		{
			// 좌표를 타일크기로 나눠서 현재 인덱스 추출
			int iCullX = pos.x / tileSize;
			int iCullY = pos.y / tileSize;
			int iIndex = 0;

			iIndex = (i + iCullY) * tileX + (j + iCullX);

			// 예외처리
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