#pragma once


enum QUEST_TYPE
{
	QUEST_STAGE = 1

};


class Quest
{
protected:

	string _name;
	int _exp;
	int _gold;
	int _monster;
	string _description;
	string _item;
	string _questCheck;
	string _monsterName;
	string _questStage;

	QUEST_TYPE _questType;


public:
	Quest() {}
	~Quest() {}

	void init(string name, int gold, int exp, string description, string item, int monster, string questCheck, string monsterName, string questStage);



	string getName() { return this->_name; }

	int getExp() { return this->_exp; }
	int getGold() { return this->_gold; }
	int getMonster() { return this->_monster; }

	string getDescription() { return this->_description; }
	string getItem() { return this->_item; }
	string getQuestCheck() { return this->_questCheck; }
	string getMonsterName() { return this->_monsterName; }
	string getQuestStage() { return this->_questStage; }

	QUEST_TYPE getType() { return this->_questType; }

};


//======================================================================

enum STORY_TYPE
{
	FIRSTSTORY_STAGE = 0,
	MINO_STAGE

};

class StoryQuest
{
protected:
	
	STORY_TYPE _storyType;
	string _storyStr;


public:
	StoryQuest() {}
	~StoryQuest() {}

	void init(STORY_TYPE type, string storyStr);
	void init(string storyStr);

	STORY_TYPE getType() { return this->_storyType; }
	string getStr() { return this->_storyStr; }
};