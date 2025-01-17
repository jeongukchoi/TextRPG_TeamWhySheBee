#pragma once

#include "BaseMonster.h"
#include <string>

using namespace std;

class Orc : public BaseMonster
{
public:
	Orc(const string& name, const int& PlayerLevel) : BaseMonster(name, PlayerLevel)
	{
		Speed = 3;
		MaxHP = static_cast<int>(MaxHP * 1.5);
		CurrentHP = MaxHP;
	}
	string EnragedSkill() override;
};


