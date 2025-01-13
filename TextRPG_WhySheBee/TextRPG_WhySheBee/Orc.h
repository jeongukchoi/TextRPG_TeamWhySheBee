#pragma once

#include "BaseMonster.h"
#include <string>

using namespace std;

class Orc : public BaseMonster
{
public:
	Orc(const string& name, const int& PlayerLevel) : BaseMonster(name, PlayerLevel) {}
	void EnragedSkill() override;
};


