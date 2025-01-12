#include "Framework.h"
#include "SwordUpgrade.h"

SwordUpgrade::SwordUpgrade(Equipment* e) : EquipmentDecorator(e), TargetStat(ATTACK), UpgradeAmount(5)
{
	switch (equipment->GetEquipmentLevel())
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

void SwordUpgrade::PrintItemInfo()
{
	equipment->PrintItemInfo();
	if (UpgradeName != "")
	{
		cout << "+" << UpgradeName << " (공격력 +" << UpgradeAmount << ")\n";
	}
}

void SwordUpgrade::Use()
{
	equipment->Use();
	PlayerCharacter* character = PlayerCharacter::GetInstance();
	character->IncreaseStat(TargetStat, UpgradeAmount);
}



