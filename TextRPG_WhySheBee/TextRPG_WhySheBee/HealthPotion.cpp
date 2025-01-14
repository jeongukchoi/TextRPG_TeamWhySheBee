#include "Framework.h"
#include "HealthPotion.h"

HealthPotion::HealthPotion() : ItemName("체력 회복 물약"), Type(CONSUMABLES), Price(100), TargetStat(HP), StatAmount(50)
{
}

void HealthPotion::Use()
{
	PlayerCharacter* character = PlayerCharacter::GetPlayer();
	character->IncreaseStat(TargetStat, StatAmount);
	cout << GetTargetStatString() << "이 " << StatAmount << " 회복되었습니다.\n현재 체력 : " << character->GetHealth() << " / 최대 체력 : " << character->GetMaxHealth();
}

void HealthPotion::PrintItemInfo()
{
	cout << "\n아이템: " << ItemName << "\n가격: " << Price << "\n효과: " << GetTargetStatString() << " +" << StatAmount << endl << endl;
}

