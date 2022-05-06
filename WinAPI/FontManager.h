#pragma once
#include "SingletonBase.h"
#include <atlbase.h>

class FontManager : public SingletonBase <FontManager>
{
public:
	FontManager() {}
	~FontManager() {}

	void drawText(HDC hdc, int destX, int destY, char* fileName, char* fontName, int fontSize, int fontWidth,
		char* printString, int length, COLORREF color);

	void drawText(HDC hdc, int destX, int destY, char* fontName, int fontSize, int fontWidth,
		char* printString, int length, COLORREF color);

	void drawText(HDC hdc, int destX, int destY, char* fontName, int fontSize, int fontWidth,
		LPCWSTR printString, int length, COLORREF color);
	void firstLineText(HDC hdc, LPCWSTR printString);
	void firstLineText(HDC hdc, LPCWSTR printString,int destX, int destY);
	void firstLineText(HDC hdc, RECT rc, string printString,int destX, int destY);

	void drawText(HDC hdc, int destX, int destY, char* fontName, int fontSize, int fontWidth,
		LPCWSTR* printStringArr, int length, COLORREF color);

	void drawText(HDC hdc, RECT rc, char* fontName, int fontSize, int fontWidth,
		string str, COLORREF color, bool clip = false);

	void boxDrawText(HDC hdc, RECT rc, char* fontName, int fontSize, int fontWidth,
		LPCWSTR printString, COLORREF color, bool clip);






};

