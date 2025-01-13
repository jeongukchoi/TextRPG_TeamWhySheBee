#include "Framework.h"
#include "AttackBoost.h"

AttackBoost::AttackBoost() : ItemName("공격력 증가 물약 (1턴간 유효)"), Type(CONSUMABLES), Price(200), TargetStat(ATTACK), StatAmount(10)
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


