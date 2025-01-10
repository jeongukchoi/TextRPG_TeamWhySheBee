#pragma once

// 각 몬스터 클래스 스킬은 추후 변경될 수 있습니다.
class Goblin : public BaseMonster
{
public:
	Goblin(const string& name, const int& PlayerLevel) : BaseMonster(name, PlayerLevel) {}

	void UseSkill() override;

};

