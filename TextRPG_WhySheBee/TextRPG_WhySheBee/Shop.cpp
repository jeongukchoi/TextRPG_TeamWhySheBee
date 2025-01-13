#include "Framework.h"
#include "Shop.h"

void Shop::UpgradeEquipment()
{	
	while (true)
	{
		cout << "\n어떤 장비를 강화하시겠습니까?\n  1: 무기\n  2: 갑옷\n  0: 나가기\n번호를 입력하세요: ";

		int Choice;
		cin >> Choice;

		PlayerCharacter* character = PlayerCharacter::GetPlayer();
		Equipment* sword = reinterpret_cast<Equipment*>(_ItemManager.GetItem(SWORD));
		Equipment* armor = reinterpret_cast<Equipment*>(_ItemManager.GetItem(ARMOR));

		switch (Choice)
		{
		case 1:
			
			//if (sword를 보유 중)
				// if (돈이 충분함)
				UpgradeSword(sword, character);
				break;
				// else
				//cout << "\n골드가 모자랍니다!\n";
				//break;
			// else
			//cout << "\n무기를 보유하고 있지 않습니다.\n";
			//break;

		case 2:
			// if (armor를 보유 중)
				// if (돈이 충분함)
				UpgradeArmor(armor, character);
				break;
				// else
				//cout << "\n골드가 모자랍니다!\n";
				//break;
			// else
			//cout << "\n갑옷을 보유하고 있지 않습니다.\n";
			//break;

		case 0:
			return;

		default:
			cout << "\n유효하지 않은 번호입니다. 번호를 다시 입력하세요.\n";
		}
	}
}

void Shop::UpgradeSword(Equipment* sword, PlayerCharacter* character)
{
	// if (장비를 착용 중)
		// 장비 해제 (무기의 업그레이드 종류가 다양한 경우 장비 해제 함수 필요)
		cout << "\n강화를 위해 장비를 해제합니다.\n";
		character->IncreaseStat(sword->GetTargetStat(), sword->GetStatAmount() * -1);
			
	if (rand() % 100 < UpgradeSuccessRate(sword))
	{
		sword = new SwordUpgrade(sword);
	}
	else
	{
		cout << "...강화에 실패하였습니다...다음에는 꼭 성공할테니 너무 상심치 마세요!\n";
	}
	sword->Use();
}

void Shop::UpgradeArmor(Equipment* armor, PlayerCharacter* character)
{
	// if (장비를 착용 중)
		// 장비 해제 (무기의 업그레이드 종류가 다양한 경우 장비 해제 함수 필요)
		cout << "\n강화를 위해 장비를 해제합니다.\n";
		character->IncreaseStat(armor->GetTargetStat(), armor->GetStatAmount() * -1);

	if (rand() % 100 < UpgradeSuccessRate(armor))
	{
		armor = new ArmorUpgrade(armor);
	}
	else
	{
		cout << "...강화에 실패하였습니다...다음에는 꼭 성공할테니 너무 상심치 마세요!\n";
	}
	armor->Use();
}

int Shop::UpgradeSuccessRate(Equipment* e)
{
	return 90 - e->GetEquipmentLevel() * 25;
}

