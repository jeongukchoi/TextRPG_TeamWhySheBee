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

void Shop::BuyItems()
{
	cout << "어서오세요 상점입니다 구입할 물품들을 골라보세요!" << endl;
	int Choice;
	cout << "***************판매목록***************" << endl;
	cout << "0.체력 포션 1.힘 증가 물약 2.무기 3.방어구" << endl;
	cout << "번호 선택: ";
	cin >> Choice;
	Inventory* inventory = Inventory::GetInstance();
	PlayerCharacter* character = PlayerCharacter::GetPlayer();

	switch (Choice)
	{
	case HEALTH_POTION:
		if (character->GetGold() > _ItemManager.GetItem(HEALTH_POTION)->GetPrice())
		{
			character->IncreaseStat(GOLD, _ItemManager.GetItem(HEALTH_POTION)->GetPrice() * -1);
			inventory->AddItem(HEALTH_POTION);
			cout << "체력 포션 구입 완료!" << endl;
		}
		else
		{
			cout << "골드가 부족합니다!" << endl;
		}
		break;

	case ATTACK_BOOST:
		if (character->GetGold() >= _ItemManager.GetItem(ATTACK_BOOST)->GetPrice())
		{
			character->IncreaseStat(GOLD, _ItemManager.GetItem(ATTACK_BOOST)->GetPrice() * -1);
			inventory->AddItem(ATTACK_BOOST);
			cout << "힘 증가 물약 구입 완료!" << endl;
		}
		else
		{
			cout << "골드가 부족합니다!" << endl;
		}
		break;

	case SWORD:
		if (character->GetGold() >= _ItemManager.GetItem(SWORD)->GetPrice())
		{
			character->IncreaseStat(GOLD, _ItemManager.GetItem(SWORD)->GetPrice() * -1);
			inventory->AddItem(SWORD);
			cout << "무기 구입 완료!" << endl;
		}
		else
		{
			cout << "골드가 부족합니다!" << endl;
		}
		break;

	case ARMOR:
		if (character->GetGold() >= _ItemManager.GetItem(ARMOR)->GetPrice())
		{
			character->IncreaseStat(GOLD, _ItemManager.GetItem(ARMOR)->GetPrice() * -1);
			inventory->AddItem(ARMOR);
			cout << "방어구 구입 완료!" << endl;
		}
		else
		{
			cout << "골드가 부족합니다!" << endl;
		}

		break;
	default:
		cout << "잘못 누르셨습니다 다시 선택해주세요!" << endl;
		break;
	}

	/*Shop shop;
	Item* item;
	shop.BuyItems(character,item);*/


}

void Shop::SellItems()
{

	Inventory* inventory = Inventory::GetInstance();
	PlayerCharacter* character = PlayerCharacter::GetPlayer();
	inventory->ShowInven();

	int choice;
	cout << "판매할 아이템의 번호 입력: ";
	cin >> choice;

	if (choice >= 0 && choice < inventory->GetInventory().size())
	{
		character->IncreaseStat(GOLD, inventory->GetInventory()[choice]->GetPrice() * 0.6);
		inventory->RemoveItem(inventory->GetInventory()[choice], choice);
	}
	else
	{
		cout << "잘못 입력 하셨습니다!" << endl;
	}






}
