#pragma once

#include <memory>
#include "Enums.h"

class EnemyFactory 
{
public:
	// 기본 몬스터 랜덤 생성 메서드
	static unique_ptr<BaseMonster> CreateBasicMonster(const int& PlayerLevel);
	// 보스 몬스터 생성 메서드
	static unique_ptr<BaseMonster> CreateBossMonster(const int& PlayerLevel);
private:
	// 랜덤 몬스터 타입 반환 메서드
	static MonsterType GetRandomMonsterType();
};


