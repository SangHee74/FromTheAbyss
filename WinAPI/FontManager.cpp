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
}


void FontManager::drawText(HDC hdc, int destX, int destY, char* fontName, int fontSize, int fontWidth,
	LPCWSTR* printStringArr, int length, COLORREF color)
{
	// ��������
	int arraySize = sizeof(printStringArr) / sizeof(*printStringArr);
} // <-���Ǵ� cpp���� ������ �� 


