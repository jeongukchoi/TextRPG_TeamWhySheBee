#pragma once

#include "BaseMonster.h"
#include <string>

using namespace std;

class Goblin : public BaseMonster
{
public:
	Goblin(const string& name, const int& PlayerLevel) : BaseMonster(name, PlayerLevel) {}
	void EnragedSkill() override;
};

