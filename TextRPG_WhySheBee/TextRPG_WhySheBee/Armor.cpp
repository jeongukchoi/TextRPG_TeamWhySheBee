#include "Framework.h"
#include "Armor.h"

Armor::Armor() : ItemName("레더 아머"), Type(EQUIPMENT), Price(300), TargetStat(MAXHP), StatAmount(30)
{
}

void Armor::PrintItemInfo()
{
	cout << "\n아이템: " << ItemName << "\n가격: " << Price << "\n효과: " << "최대 체력 +" << StatAmount << endl << endl;
}

void Armor::Use()
{
	PlayerCharacter* character = PlayerCharacter::GetPlayer();
	character->IncreaseStat(TargetStat, StatAmount);
}




