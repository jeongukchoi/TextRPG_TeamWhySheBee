#include "Framework.h"
#include "Sword.h"

Sword::Sword() : ItemName("배틀 소드"), Type(EQUIPMENT), Price(500), TargetStat(ATTACK), StatAmount(20)
{
}

void Sword::PrintItemInfo()
{
	cout << "\n아이템: " << ItemName << "\n가격: " << Price << "\n효과: " << "공격력 +" << StatAmount << endl << endl;
}

void Sword::Use()
{
	PlayerCharacter* character = PlayerCharacter::GetPlayer();
	character->IncreaseStat(TargetStat, StatAmount);
}


