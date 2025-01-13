#include "Framework.h"
#include "ArmorUpgrade.h"

ArmorUpgrade::ArmorUpgrade(Equipment* e) : EquipmentDecorator(e), TargetStat(MAXHP)
{
	int EquipmentLevel = equipment->GetEquipmentLevel();
	UpgradeCost = (EquipmentLevel + 1) * 150;
	UpgradeAmount = (EquipmentLevel + 1) * 20;

	switch (EquipmentLevel)
	{
	case 0:
		UpgradeName = "무두질";
		break;

	case 1:
		UpgradeName = "이음새 강화";
		break;

	case 2:
		UpgradeName = "안감 덧대기";
		break;

	case 3:
		UpgradeName = "표면 금속 코팅";
		break;

	default:
		UpgradeName = "";
		break;
	}
}

void ArmorUpgrade::PrintItemInfo()
{
	equipment->PrintItemInfo();
	if (UpgradeName != "")
	{
		cout << "+" << UpgradeName << " (체력 +" << UpgradeAmount << ")\n";
	}
}

void ArmorUpgrade::Use()
{
	equipment->Use();
	PlayerCharacter* character = PlayerCharacter::GetInstance();
	character->IncreaseStat(TargetStat, UpgradeAmount);
	character->IncreaseStat(HP, UpgradeAmount);
}


