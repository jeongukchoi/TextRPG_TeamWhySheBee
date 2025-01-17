#include "Framework.h"
#include "Armor.h"

Armor::Armor() : ItemName("레더 아머"), Type(EQUIPMENT), Price(300), TargetStat(MAXHP), StatAmount(30)
{
}

void Armor::PrintItemInfo()
{
	cout << "\n아이템: " << ItemName << "\n가격: " << Price << "\n효과: " << "최대 체력 +" << StatAmount << endl << endl;
}

string Armor::GetItemInfoString()
{
	return "아이템: " + ItemName + "\n가격: " + to_string(Price) + "\n효과: " + GetTargetStatString() + " +" + to_string(StatAmount);
}

void Armor::Use()
{
	PlayerCharacter* character = PlayerCharacter::GetPlayer();
	character->IncreaseStat(TargetStat, StatAmount);
}




