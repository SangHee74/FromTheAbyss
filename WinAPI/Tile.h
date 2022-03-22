#pragma once

//Ÿ�� ������
#define TILESIZE_X 26
#define TILESIZE_Y 26

//Ÿ�� ����
#define TILEMAX_X 50
#define TILEMAX_Y 50

//Ÿ�� �Ӽ�
enum groundType // �̵�����, �̵��Ұ� ����
{ 
	MOVE,UNMOVE
};

enum tileStage // �������� �� Ÿ�ϼ�
{
	ABYSS1,ABYSS2,ABYSS3,ABYSS4,ABYSS5,ABYSS6,ABYSS7,ABYSS8
};




class Tile
{
public:
	int x;
	int y;
	groundType moveCheck;
};

