#pragma once
#include "SingletonBase.h"

class FontManager : public SingletonBase <FontManager>
{
public:
	FontManager() {}
	~FontManager() {}

	// 파일경로 읽어올때
	void drawText(HDC hdc, int destX, int destY, char* fileName, char* fontName, int fontSize, int fontWidth,
		char* printString, int length, COLORREF color);

	void drawText(HDC hdc, int destX, int destY, char* fontName, int fontSize, int fontWidth,
		char* printString, int length, COLORREF color);

	// LPCWSTR : W -> multy char -> Unicode;
	void drawText(HDC hdc, int destX, int destY, char* fontName, int fontSize, int fontWidth,
		LPCWSTR printString, int length, COLORREF color);

	void firstLineText(HDC hdc, LPCWSTR printString);

	// 문자열로 찾음 -> 반복문으로 돈다
	void drawText(HDC hdc, int destX, int destY, char* fontName, int fontSize, int fontWidth,
		LPCWSTR* printStringArr, int length, COLORREF color);


};

