#include "Framework.h"
#include "AttackBoost.h"

AttackBoost::AttackBoost() : ItemName("AttackBoost"), TargetStat(ATTACK)
{
}

void AttackBoost::Use(PlayerCharacter* character)
{
	character->IncreaseStat(TargetStat, StatAmount);
}

void AttackBoost::PrintItemInfo()
{
	cout << "아이템: " << ItemName << "\n효과: " << "Attack +" << StatAmount << endl;
}
