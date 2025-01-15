#include "Framework.h"
#include "UniquePotion.h"

UniquePotion::UniquePotion() : ItemName("유니크 비약"), Type(CONSUMABLES), Price(300)
{
	
	PlayerCharacter* character = PlayerCharacter::GetPlayer();
	switch (character->GetPlayerJob())
	{
		// 워리어의 경우
	case WARRIOR:
		TargetStat = STR;
		StatAmount = 15;
		break;

		// 메이지의 경우
	case MAGE:
		TargetStat = INTELLGENCE;
		StatAmount = 10;
		break;


	default:
		TargetStat = (STATUS) 0;
		StatAmount = 0;
	}

}

string UniquePotion::GetTargetStatString() const
{
	PlayerCharacter* character = PlayerCharacter::GetPlayer();
	switch (character->GetPlayerJob())
	{
	// 워리어의 경우
	case WARRIOR:
		return "힘";

	// 메이지의 경우
	case MAGE:
		return "지능";

	default:
		return "";
	}
}

void UniquePotion::Use()
{
	PlayerCharacter* character = PlayerCharacter::GetPlayer();
	character->IncreaseStat(TargetStat, StatAmount);
}

string UniquePotion::GetItemInfoString()
{
	return "아이템: " + ItemName + "\n가격: " + to_string(Price) + "\n효과: " + GetTargetStatString() + " +" + to_string(StatAmount);
}

void UniquePotion::PrintItemInfo()
{
	cout << "\n아이템: " << ItemName << "\n가격: " << Price << "\n효과: " << GetTargetStatString() << " +" << StatAmount << endl << endl;
}


