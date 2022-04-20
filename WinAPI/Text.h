#pragma once


//Black Text
#define BTEXT RGB(255, 255, 255)

struct tagOnlyText
{
	LPCWSTR text;
};

struct tagText
{
	LPCWSTR name;
	LPCWSTR script;
};

struct tagImageWithText
{
	LPCWSTR name;
	string imageVec;
	LPCWSTR script;
};


struct tagImageWithText2
{
	string imageVec;
	LPCWSTR script;
};

