#pragma once

#include "BaseMonster.h"
#include "PlayerCharacter.h"

class BossMonster : public BaseMonster
{
private:
	shared_ptr<PlayerCharacter> Player = PlayerCharacter::GetInstance();

public:
	BossMonster(const string& name, const int& PlayerLevel) : BaseMonster(name, PlayerLevel) {}
	void EnragedSkill() override;
	void UseRandomSkill();
private:
	void FireBress();
	void QuickAttack();
};


