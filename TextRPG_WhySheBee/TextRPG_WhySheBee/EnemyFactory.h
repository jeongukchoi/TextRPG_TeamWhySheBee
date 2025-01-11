#pragma once

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
	static BaseMonster* CreateBasicMonster(const int& PlayerLevel);
	static BaseMonster* CreateBossMonster(const int& PlayerLevel);
private:
	static MonsterType GetRandomMonsterType();
};

