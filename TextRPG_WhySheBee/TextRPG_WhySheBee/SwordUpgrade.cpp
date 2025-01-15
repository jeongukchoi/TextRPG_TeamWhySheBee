#include "Framework.h"
#include "SwordUpgrade.h"

SwordUpgrade::SwordUpgrade(Equipment* e) : EquipmentDecorator(e), TargetStat(ATTACK)
{
	// 강화 전 레벨 기준
	switch (GetEquipmentLevel() - 1)
	{
	case 0:
		UpgradeName = "칼날 다듬기";
		break;

	case 1:
		UpgradeName = "손잡이 경량화";
		break;

	case 2:
		UpgradeName = "장인의 특별 개조";
		break;

	case 3:
		UpgradeName = "아다만티움 코팅";
		break;

	default:
		UpgradeName = "";
		break;
	}
}

string SwordUpgrade::GetItemInfoString()
{
	return "아이템: " + GetName() + "(+" + to_string(GetEquipmentLevel()) + ")"
		+ "\n가격: " + to_string(GetPrice()) + "\n효과: " + GetTargetStatString() + " +" + to_string(GetStatAmount());
}

void SwordUpgrade::PrintItemInfo()
{
	cout << "\n아이템: " << GetName() << "(+" << GetEquipmentLevel() << ")"
		<< "\n가격: " << GetPrice() << "\n효과: " << GetTargetStatString() << " +" << GetStatAmount() << endl << endl;
}

void SwordUpgrade::Use()
{
	equipment->Use();
	PlayerCharacter* character = PlayerCharacter::GetPlayer();
	character->IncreaseStat(TargetStat, GetUpgradeAmount());
}




