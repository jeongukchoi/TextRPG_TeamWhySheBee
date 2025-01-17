#include "Framework.h"
#include "AttackBoost.h"

AttackBoost::AttackBoost() : ItemName("공격력 비약"), Type(CONSUMABLES), Price(200), TargetStat(ATTACK), StatAmount(10)
{
}

void AttackBoost::Use()
{
	PlayerCharacter* character = PlayerCharacter::GetPlayer();
	character->IncreaseStat(TargetStat, StatAmount);
}

string AttackBoost::GetItemInfoString()
{
	return "아이템: " + ItemName + "\n가격: " + to_string(Price) + "\n효과: " + GetTargetStatString() + " +" + to_string(StatAmount);
}

void AttackBoost::PrintItemInfo()
{
	cout << "\n아이템: " << ItemName << "\n가격: " << Price << "\n효과: " << GetTargetStatString() << " +" << StatAmount << endl << endl;
}


