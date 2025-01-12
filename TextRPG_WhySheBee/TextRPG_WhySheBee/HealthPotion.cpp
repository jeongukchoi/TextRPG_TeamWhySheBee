#include "Framework.h"
#include "HealthPotion.h"

HealthPotion::HealthPotion() : ItemName("HealthPotion"), TargetStat(HP)
{
}

void HealthPotion::Use(PlayerCharacter* character)
{
	character->IncreaseStat(TargetStat, StatAmount);
}

void HealthPotion::PrintItemInfo()
{
	cout << "아이템: " << ItemName << "\n효과: " << "Health +" << StatAmount << endl;
}