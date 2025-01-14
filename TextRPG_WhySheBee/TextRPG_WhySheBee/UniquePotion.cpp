#include "Framework.h"
#include "UniquePotion.h"

UniquePotion::UniquePotion() : ItemName("유니크 스탯 증가 비약"), Type(CONSUMABLES), Price(300)
{
	
	PlayerCharacter* character = PlayerCharacter::GetPlayer();
	switch (character->GetJob())
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
	}
}

void UniquePotion::Use()
{
	PlayerCharacter* character = PlayerCharacter::GetPlayer();
	character->IncreaseStat(TargetStat, StatAmount);
	cout << GetTargetStatString() << "이 " << StatAmount << " 증가하였습니다.\n"
		<< "현재 " << GetTargetStatString() << ": " << character->GetUniqueStat();
}

void UniquePotion::PrintItemInfo()
{
	cout << "\n아이템: " << ItemName << "\n가격: " << Price << "\n효과: " << GetTargetStatString() << " +" << StatAmount << endl << endl;
}


