#include "Framework.h"
#include "HealthPotion.h"

HealthPotion::HealthPotion() : ItemName("HealthPotion"), TargetStat(HP)
{
}

void HealthPotion::Use(PlayerCharacter* character)
{
	cout << "HealthPotion 포션을 사용해 공격력이 " << StatAmount << " 증가합니다." << endl;
	character->IncreaseStat(TargetStat, StatAmount);
}

void HealthPotion::PrintItemInfo()
{
	cout << "아이템: " << ItemName << "\n효과: " << "Health +" << StatAmount << endl;
}