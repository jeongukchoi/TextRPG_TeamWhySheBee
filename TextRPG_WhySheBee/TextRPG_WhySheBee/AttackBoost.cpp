#include "Framework.h"
#include "AttackBoost.h"

AttackBoost::AttackBoost() : ItemName("공격력 증가 물약 (1턴간 유효)"), Type(CONSUMABLES), Price(200), TargetStat(ATTACK), StatAmount(10)
{
}

void AttackBoost::Use()
{
	PlayerCharacter* character = PlayerCharacter::GetPlayer();
	character->IncreaseStat(TargetStat, StatAmount);
	cout << GetTargetStatString() << "이 " << StatAmount << " 증가하였습니다.\n현재 " << GetTargetStatString() << " : " << character->GetAttack();
}

void AttackBoost::PrintItemInfo()
{
	cout << "\n아이템: " << ItemName << "\n가격: " << Price << "\n효과: " << GetTargetStatString() << " +" << StatAmount << endl << endl;
}


