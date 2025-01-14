#pragma once

#include "BaseMonster.h"
#include <string>

using namespace std;

class Goblin : public BaseMonster
{
public:
	Goblin(const string& name, const int& PlayerLevel) : BaseMonster(name, PlayerLevel)
	{
		Damage = static_cast<int>(Damage * 0.4f);
		Speed = 2;
	}
	void EnragedSkill() override;
};


