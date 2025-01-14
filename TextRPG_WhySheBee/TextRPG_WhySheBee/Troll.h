#pragma once

#include "BaseMonster.h"
#include <string>

using namespace std;

class Troll : public BaseMonster
{
public:
	Troll(const string& name, const int& PlayerLevel) : BaseMonster(name, PlayerLevel)
	{
		Speed = 4;
		//Damage = static_cast<int>(Damage * 1.2);
	}
	void EnragedSkill() override;
};

