#include "Framework.h"

// 기본 몬스터 랜덤 생성 메서드
unique_ptr<BaseMonster> EnemyFactory::CreateBasicMonster(const int& PlayerLevel)
{
	MonsterType Type = GetRandomMonsterType();

	switch (Type)
	{
	case GOBLIN:
		return make_unique<Goblin>("고블린", PlayerLevel);
	case ORC:
		return make_unique<Orc>("오크", PlayerLevel);
	case SLIME:
		return make_unique<Slime>("슬라임", PlayerLevel);
	case TROLL:
		return make_unique<Troll>("트롤", PlayerLevel);
	default:
		throw runtime_error("== 기본 몬스터 타입, 오류 발생 ==");
	}
}

//보스 몬스터 생성 메서드
unique_ptr<BaseMonster> EnemyFactory::CreateBossMonster(const int& PlayerLevel)
{
	return make_unique<BossMonster>("레드 드래곤", PlayerLevel);
}

// 랜덤 몬스터 타입 반환 메서드
MonsterType EnemyFactory::GetRandomMonsterType()
{
	int RandomValue = rand() % 4;

	return static_cast<MonsterType>(RandomValue);
}

