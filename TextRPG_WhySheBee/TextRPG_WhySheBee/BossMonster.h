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
		// 기본 몬스터의 체력 5배
		MaxHP *= 5;
		CurrentHP = MaxHP;
		
		// 기본 몬스터의 공격력의 1.5배 데미지 적용
		Damage += static_cast<int>(Damage * 1.5);

		// 공격 속도
		Speed = 6;
	}

	// 분노 상태 스킬 메서드
	string EnragedSkill() override;
	// Boss 전용 스킬 랜덤 선택 메서드
	string UseRandomSkill();

private:
	// Boss 전용 스킬 메서드
	void FireBress();
	void QuickAttack();
};


