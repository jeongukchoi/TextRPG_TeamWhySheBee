#pragma once

#include <memory>
#include "Enums.h"

class EnemyFactory 
{
public:
	static unique_ptr<BaseMonster> CreateBasicMonster(const int& PlayerLevel);
	static unique_ptr<BaseMonster> CreateBossMonster(const int& PlayerLevel);
private:
	static MonsterType GetRandomMonsterType();
};


