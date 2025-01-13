#pragma once

#include "BaseMonster.h"
#include <string>

using namespace std;

class Troll : public BaseMonster
{
public:
	Troll(const string& name, const int& PlayerLevel) : BaseMonster(name, PlayerLevel) {}
	void EnragedSkill() override;
};

