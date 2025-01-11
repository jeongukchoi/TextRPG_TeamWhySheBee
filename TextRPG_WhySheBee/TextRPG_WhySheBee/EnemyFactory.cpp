#include "Framework.h"

BaseMonster* EnemyFactory::CreateBasicMonster(const int& PlayerLevel)
{
	MonsterType Type = GetRandomMonsterType();

	switch (Type)
	{
	case GOBLIN:
		return new Goblin("고블린", PlayerLevel);
	case ORC:
		return new Orc("오크", PlayerLevel);
	case SLIME:
		return new Slime("슬라임", PlayerLevel);
	case TROLL:
		return new Troll("트롤", PlayerLevel);
	}
}

BaseMonster* EnemyFactory::CreateBossMonster(const int& PlayerLevel)
{
	return new BossMonster("레드 드래곤", PlayerLevel);
}

MonsterType EnemyFactory::GetRandomMonsterType()
{
	int RandomValue = rand() % 4;

	return static_cast<MonsterType>(RandomValue);
}
