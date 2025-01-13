#pragma once

#include <memory>

enum MonsterType
{
	GOBLIN,
	ORC,
	SLIME,
	TROLL,
};

class EnemyFactory 
{
public:
	static unique_ptr<BaseMonster> CreateBasicMonster(const int& PlayerLevel);
	static unique_ptr<BaseMonster> CreateBossMonster(const int& PlayerLevel);
private:
	static MonsterType GetRandomMonsterType();
};

