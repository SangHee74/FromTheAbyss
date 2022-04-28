#include "Stdafx.h"
#include "Quest.h"

void Quest::init(string name, int gold, int exp, string description, string item, int monster, string questCheck, string monsterName, string questStage)
{
	_name = name;
	_gold = gold;
	_exp = exp;
	_description = description;
	_item = item;
	_monster = monster;
	_questCheck = questCheck;
	_monsterName = monsterName;
	_questStage = questStage;
}


void StoryQuest::init(STORY_TYPE type, string storyStr)
{
	_storyType = type;

	_storyStr = storyStr;
}

void StoryQuest::init(string storyStr)
{
	_storyStr = storyStr;
}