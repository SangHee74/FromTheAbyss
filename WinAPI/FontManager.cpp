#include "Stdafx.h"
#include "FontManager.h"



void FontManager::drawText(HDC hdc, int destX, int destY, char* fileName, char* fontName, int fontSize, int fontWidth, char* printString, int length, COLORREF color)
{
}

void FontManager::drawText(HDC hdc, int destX, int destY, char* fontName, int fontSize, int fontWidth, char* printString, int length, COLORREF color)
{
}

void FontManager::drawText(HDC hdc, int destX, int destY, char* fontName, int fontSize, int fontWidth, LPCWSTR printString, int length, COLORREF color)
{
	SetBkMode(hdc, TRANSPARENT);

		/*
		font = CreateFont
		(
			����ũ��, ������, ���� ��ü ����, ���� ����, ���� ����,
			����(true, false), ����(true, false), ��Ҽ�(true, false),
			���ڼ���, ��� ��Ȯ��, Ŭ���� ��Ȯ��, ����� ��, �ڰ�, ��Ʈ
		)*/

		HFONT hFont = CreateFont
		(
			fontSize,0,0,5,fontWidth,
			0,0,0,
			HANGEUL_CHARSET, 0,0,0,
			VARIABLE_PITCH|FF_ROMAN , TEXT(fontName)
		);

		auto oldFont = (HFONT)SelectObject(hdc, hFont);
		auto oldColor = GetTextColor(hdc);

		SetTextColor(hdc, color);
		TextOutW(hdc, destX, destY, printString, length);

		SelectObject(hdc, oldFont);
		DeleteObject(hFont);


}


void FontManager::firstLineText(HDC hdc, LPCWSTR printString)
{
	SetBkMode(hdc, TRANSPARENT);

	HFONT hFont = CreateFont
	(
		21, 0, 0, 5, FW_MEDIUM,
		0, 0, 0,
		HANGEUL_CHARSET, 0, 0, 0,
		VARIABLE_PITCH | FF_ROMAN, TEXT("����")
	);

	auto oldFont = (HFONT)SelectObject(hdc, hFont);
	auto oldColor = GetTextColor(hdc);

	SetTextColor(hdc, RGB(0, 0, 0));
	TextOutW(hdc, 35, 350, printString, wcslen(printString));

	SelectObject(hdc, oldFont);
	DeleteObject(hFont);
}


void FontManager::firstLineText(HDC hdc, LPCWSTR printString, int destX, int destY)
{
	SetBkMode(hdc, TRANSPARENT);

	HFONT hFont = CreateFont
	(
		21, 0, 0, 5, FW_MEDIUM,
		0, 0, 0,
		HANGEUL_CHARSET, 0, 0, 0,
		VARIABLE_PITCH | FF_ROMAN, TEXT("����")
	);

	auto oldFont = (HFONT)SelectObject(hdc, hFont);
	auto oldColor = GetTextColor(hdc);

	SetTextColor(hdc, RGB(0, 0, 0));
	TextOutW(hdc, destX, destY, printString, wcslen(printString));

	SelectObject(hdc, oldFont);
	DeleteObject(hFont);
}


void FontManager::firstLineText(HDC hdc, RECT rc, string printString, int destX, int destY)
{
	SetBkMode(hdc, TRANSPARENT);

	HFONT hFont = CreateFont
	(
		21, 0, 0, 5, FW_MEDIUM,
		0, 0, 0,
		HANGEUL_CHARSET, 0, 0, 0,
		VARIABLE_PITCH | FF_ROMAN, TEXT("����")
	);

	auto oldFont = (HFONT)SelectObject(hdc, hFont);
	auto oldColor = GetTextColor(hdc);

	SetTextColor(hdc, RGB(0, 0, 0));
	DrawText(hdc, printString.c_str(), strlen(printString.c_str()), &rc, DT_LEFT || DT_NOCLIP);

	SelectObject(hdc, oldFont);
	DeleteObject(hFont);
}



void FontManager::drawText(HDC hdc, int destX, int destY, char* fontName, int fontSize, int fontWidth,
	LPCWSTR* printStringArr, int length, COLORREF color)
{
	// ��������
	int arraySize = sizeof(printStringArr) / sizeof(*printStringArr);
} // <-���Ǵ� cpp���� ������ �� 



void FontManager::drawText(HDC hdc, RECT rc, char* fontName, int fontSize, int fontWidth, string str, COLORREF color, bool clip)
{
	SetBkMode(hdc, TRANSPARENT);

	HFONT hFont = CreateFont
	(
		21, 0, 0, 5, fontWidth,
		0, 0, 0,
		HANGEUL_CHARSET, 0, 0, 0,
		VARIABLE_PITCH | FF_ROMAN, TEXT(fontName)
	);

	auto oldFont = (HFONT)SelectObject(hdc, hFont);
	auto oldColor = GetTextColor(hdc);

	SetTextColor(hdc, color);

	if (!clip) 
	{
		DrawText(hdc,str.c_str(), strlen(str.c_str()), &rc, DT_LEFT|| DT_NOCLIP);

	}
	else {

		DrawText(hdc,str.c_str(), strlen(str.c_str()), &rc, DT_LEFT|| DT_WORDBREAK);
	}
	
	SelectObject(hdc, oldFont);
	DeleteObject(hFont);
}

void FontManager::boxDrawText(HDC hdc, RECT rc, char* fontName, int fontSize, int fontWidth, LPCWSTR printString, COLORREF color, bool clip)
{
	
	USES_CONVERSION;
	LPCWSTR wChar = printString;
	LPCSTR mChar;
	mChar = W2A(wChar);

	SetBkMode(hdc, TRANSPARENT);

	HFONT hFont = CreateFont
	(
		21, 0, 0, 5, fontWidth,
		0, 0, 0,
		HANGEUL_CHARSET, 0, 0, 0,
		VARIABLE_PITCH | FF_ROMAN, TEXT(fontName)
	);

	auto oldFont = (HFONT)SelectObject(hdc, hFont);
	auto oldColor = GetTextColor(hdc);

	SetTextColor(hdc, color);

	if (!clip)
	{
		DrawText(hdc, mChar, strlen(mChar), &rc, DT_LEFT || DT_NOCLIP);
	}
	else
	{
		DrawText(hdc, mChar, strlen(mChar), &rc, DT_LEFT || DT_WORDBREAK);
	}

	SelectObject(hdc, oldFont);
	DeleteObject(hFont);
}



