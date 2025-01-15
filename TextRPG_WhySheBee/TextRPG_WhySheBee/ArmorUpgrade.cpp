#include "Framework.h"
#include "ArmorUpgrade.h"

ArmorUpgrade::ArmorUpgrade(Equipment* e) : EquipmentDecorator(e), TargetStat(MAXHP)
{
	// 강화 전 레벨 기준
	switch (GetEquipmentLevel() - 1)
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

string ArmorUpgrade::GetItemInfoString()
{
	return "아이템: " + GetName() + "(+" + to_string(GetEquipmentLevel()) + ")"
		+ "\n가격: " + to_string(GetPrice()) + "\n효과: " + GetTargetStatString() + " +" + to_string(GetStatAmount());
}

void ArmorUpgrade::PrintItemInfo()
{
	cout << "\n아이템: " << GetName() << "(+" << GetEquipmentLevel() << ")"
		<< "\n가격: " << GetPrice() << "\n효과: " << GetTargetStatString() << " +" << GetStatAmount() << endl << endl;
}

void ArmorUpgrade::Use()
{
	equipment->Use();
	PlayerCharacter* character = PlayerCharacter::GetPlayer();
	character->IncreaseStat(TargetStat, GetUpgradeAmount());
}


