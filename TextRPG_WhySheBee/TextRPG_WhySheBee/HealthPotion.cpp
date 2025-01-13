#include "Framework.h"
#include "HealthPotion.h"

HealthPotion::HealthPotion() : ItemName("체력 회복 물약"), Type(CONSUMABLES), Price(100), TargetStat(HP), StatAmount(50)
{
}

void HealthPotion::Use()
{
	PlayerCharacter* character = PlayerCharacter::GetInstance();
	character->IncreaseStat(TargetStat, StatAmount);
}

void HealthPotion::PrintItemInfo()
{
	cout << "\n아이템: " << ItemName << "\n가격: " << Price << "\n효과: " << "체력 +" << StatAmount << endl;
}

