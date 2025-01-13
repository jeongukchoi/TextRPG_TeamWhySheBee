#pragma once

#include "BaseMonster.h"
#include "PlayerCharacter.h"
#include <string>

using namespace std;

class Slime : public BaseMonster
{
public:
	Slime(const string& name, const int& PlayerLevel) : BaseMonster(name, PlayerLevel) {}
	void EnragedSkill() override;
private:
	shared_ptr<PlayerCharacter> Player = PlayerCharacter::GetInstance();
};


