#include "Framework.h"
#include "AttackBoost.h"

AttackBoost::AttackBoost() : ItemName("AttackBoost"), Type(CONSUMABLES), Price(200), TargetStat(ATTACK), StatAmount(10)
{
}

void AttackBoost::Use()
{
	PlayerCharacter* character = PlayerCharacter::GetInstance();
	character->IncreaseStat(TargetStat, StatAmount);
}

void AttackBoost::PrintItemInfo()
{
	cout << "\n아이템: " << ItemName << "\n가격: " << Price << "\n효과: " << "Attack +" << StatAmount << endl;
}


