#include "Framework.h"
#include "Sword.h"

Sword::Sword() : ItemName("검"), Type(EQUIPMENT), Price(500), TargetStat(ATTACK), StatAmount(10)
{
}

void Sword::PrintItemInfo()
{
	cout << "\n아이템: " << ItemName << "\n가격: " << Price << "\n효과: " << "공격력 +" << StatAmount << endl;
}

void Sword::Use()
{
	PlayerCharacter* character = PlayerCharacter::GetInstance();
	character->IncreaseStat(TargetStat, StatAmount);
}

