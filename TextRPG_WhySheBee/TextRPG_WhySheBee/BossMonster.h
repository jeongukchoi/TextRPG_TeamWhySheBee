#pragma once

#include "BaseMonster.h"
#include "PlayerCharacter.h"

class BossMonster : public BaseMonster
{
private:
	PlayerCharacter* Player = PlayerCharacter::GetPlayer();

public:
	BossMonster(const string& name, const int& PlayerLevel) : BaseMonster(name, PlayerLevel)
	{
		// 기본 몬스터의 체력 3배
		MaxHP *= 3;
		CurrentHP = MaxHP;
		
		// 기본 몬스터의 공격력 30 추가
		Damage += 30;

		// 공격 속도
		Speed = 10;
	}

	// 분노 상태 스킬 메서드
	void EnragedSkill() override;
	// Boss 전용 스킬 랜덤 선택 메서드
	void UseRandomSkill();

private:
	// Boss 전용 스킬 메서드
	void FireBress();
	void QuickAttack();
};


