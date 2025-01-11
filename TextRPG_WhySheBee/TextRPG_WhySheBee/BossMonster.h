#pragma once

#include "BaseMonster.h"
#include "PlayerCharacter.h"

class BossMonster : public BaseMonster
{
private:
	PlayerCharacter* Player = PlayerCharacter::GetInstance();

public:
	BossMonster(const string& name, const int& PlayerLevel) : BaseMonster(name, PlayerLevel) {}
	void EnragedSkill() override;
	void UseRandomSkill();
private:
	void FireBress();
	void QuickAttack();
};