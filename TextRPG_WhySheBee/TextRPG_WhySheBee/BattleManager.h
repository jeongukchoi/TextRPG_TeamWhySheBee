#pragma once

#include "PlayerCharacter.h"

class BattleManager
{
private:
	PlayerCharacter* Player;
	BaseMonster* Monster;
	int PlayerLevel;

public:
	BattleManager() : Player(PlayerCharacter::GetInstance()), Monster(nullptr), PlayerLevel(0) {}
	~BattleManager() { delete Monster; }

	// 전투 메서드(플레이어의 승,패 여부를 반환합니다)
	bool Battle();

	BaseMonster* GetMonster() const { return  Monster; };

private:
	// 몬스터 생성 메서드
	void CreateMonster();

	// 플레이어 공격 메서드
	void PlayerAttack();
	// 몬스터 공격 메서드
	void MonsterAttack();

	// 플레이어 사망 체크
	bool IsPlayerDead();
	// 몬스터 사망 체크
	bool IsMonsterDead();

	// 몬스터 삭제
	void DeleteMonster();
};

