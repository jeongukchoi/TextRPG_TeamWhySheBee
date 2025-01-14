#include "Framework.h"
#include "Shop.h"
#undef max

Shop::Shop()
{
	PInventory = Inventory::GetInstance();
}

void Shop::StartShop()
{
	cout << "\n(수염이 덥수룩하고 허리가 살짝 굽어 애처로운 모습의 상점 주인이 힙겹게 인사를 건넨다.)\n";
	cout << "상점 주인: 어서...오세요...콜록...오늘은...무슨 일로...?\n";
	while (true)
	{
		cout << "\n(아래 번호를 입력해 원하는 메뉴로 진입하세요.)\n1: 아이템 구매\n2: 아이템 판매\n3: 장비 강화\n4: 상점 주인과 차 마시기\n0: 상점 나가기\n번호를 입력하세요: ";

		int Choice;
		cin >> Choice;
		switch (Choice)
		{
		case 1:
			BuyItems();
			break;

		case 2:
			SellItems();
			break;

		case 3:
			UpgradeEquipment();
			break;

		case 4:
			DrinkTea();
			break;
		
		case 0:
			cout << "\n(상점 주인이 아쉬운 듯 내 얼굴을 흘끔 바라본다.)\n";
			cout << "그렇군요...갈 길이 바쁘시겠지요...그럼...행운을 빕니다...\n(상점 주인의 응원에 힘입어 가벼운 마음으로 상점을 나섰다.)\n\n";
			Sleep(1000);
			return;
		}
	}
}

void Shop::BuyItems()
{
	Inventory* inventory = Inventory::GetInstance();
	PlayerCharacter* character = PlayerCharacter::GetPlayer();
	ItemManager IM;
	const vector<Item*>& ItemDB = IM.GetItemsList();

	cout << "구입할 물품을 골라보세요!" << endl;
	while (true)
	{
		cout << "\n***************상점 아이템 목록***************" << endl;
		cout << "(현재 소지한 골드: " << character->GetGold() << ")" << endl;

		IM.ShowItemDB();
		cout << "0: 상점 메뉴로 돌아가기\n\n";
		cout << "번호를 입력하세요: ";
		int Choice;
		cin >> Choice;
		Choice--;

		if (Choice == -1)
		{
			cout << "\n상점 메뉴로 돌아갑니다.\n";
			return;
		}
		else if (Choice >= 0 && Choice < ItemDB.size())
		{
			if (character->GetGold() < ItemDB[Choice]->GetPrice())
			{
				cout << "\n!----골드가 부족합니다!----!\n\n";
				continue;
			}
			// 골드 차감 후 인벤토리에 추가
			character->IncreaseStat(GOLD, ItemDB[Choice]->GetPrice() * -1);
			inventory->AddItem(ItemDB[Choice]->GetID());
		}
		else
		{
			cout << "\n유효하지 않은 입력입니다.\n";
		}
	}
}

void Shop::SellItems()
{
	Inventory* inventory = Inventory::GetInstance();
	PlayerCharacter* character = PlayerCharacter::GetPlayer();

	cout << "판매할 물품을 골라보세요!" << endl;
	while (true)
	{
		inventory->ShowInven();
		cout << "0: 상점 메뉴로 돌아가기\n\n";
		int choice;
		cout << "번호를 입력하세요: ";
		cin >> choice;
		choice--;

		if (choice == -1)
		{
			cout << "\n상점 메뉴로 돌아갑니다.\n";
			return;
		}
		else if (choice >= 0 && choice < inventory->GetInventory().size())
		{
			character->IncreaseStat(GOLD, inventory->GetInventory()[choice]->GetPrice() * 0.6); // double ->int 어떻게?
			inventory->RemoveItem(inventory->GetInventory()[choice], choice);
			cout << "\n현재 소지한 골드: " << character->GetGold() << endl;
		}
		else
		{
			cout << "잘못 입력 하셨습니다!" << endl;
		}
	}
}

void Shop::DrinkTea()
{
	cout << "\n(상점 주인이 따뜻한 녹차를 내온다. 덜덜 떨리는 손에 들린 잔이 잔받침과 부딪혀 달그락거린다.)\n";
	cout << "상점 주인: 여행하시느라...힘드시겠어요...차가 뜨거우니...천천히...드세요...\n";
	cout << "\n......차 마시는 중......\n";
	for (int i = 0; i < 6; i++)
	{
		Sleep(1000);
		cout << "...";
	}
	cout << "\n(몸에 따뜻한 기운이 퍼진다. 주인과 이런저런 이야기를 나누며 마음이 편안해졌다.)\n";
}

void Shop::UpgradeEquipment()
{
	PlayerCharacter* character = PlayerCharacter::GetPlayer();
	vector<Item*> _Inventory = PInventory->GetInventory();

	cout << "\n|++++++++++|장비 강화|++++++++++|\n";

	while(true)
	{
		// 인벤 출력
		PInventory->ShowInven();

		cout << "0: 상점 메뉴로 돌아가기\n강화할 아이템의 번호를 입력하세요.\n입력: ";

		int i;
		cin >> i;
		i--;

		if (i == -1)
		{
			cout << "\n상점 메뉴로 돌아갑니다.\n";
			break;
		}

		if (i < 0 || i >= _Inventory.size())
		{
			cout << "\n잘못된 입력입니다.\n";
			Sleep(500);
			continue;
		}

		// 장비 아닌 아이템은 패스
		if (_Inventory[i]->GetType() != EQUIPMENT)
		{
			cout << "\n선택한 아이템이 장비 아이템이 아닙니다.\n";
			Sleep(500);
			continue;
		}

		// 강화 정보를 반환하기 위한 임시 값들
		//string UpgradeName;
		int UpgradeAmount;
		int UpgradeCost;
		ItemID ID = _Inventory[i]->GetID();

		if (ID == ARMOR)
		{
			//UpgradeName = ArmorUpgrade(ItemToUpgrade).GetUpgradeName();
			UpgradeAmount = dynamic_cast<Equipment*>(_Inventory[i])->GetUpgradeAmount() + ARMOR_UPGRADE_AMOUNT;
			UpgradeCost = dynamic_cast<Equipment*>(_Inventory[i])->GetUpgradeCost() + ARMOR_UPGRADE_COST;
		}
		else if (ID == SWORD)
		{
			//UpgradeName = SwordUpgrade(ItemToUpgrade).GetUpgradeName();
			UpgradeAmount = dynamic_cast<Equipment*>(_Inventory[i])->GetUpgradeAmount() + SWORD_UPGRADE_AMOUNT;
			UpgradeCost = dynamic_cast<Equipment*>(_Inventory[i])->GetUpgradeCost() + SWORD_UPGRADE_COST;
		}
		else
		{
			throw runtime_error("----강화 중 유효하지 않은 ID가 발견되었습니다.");
		}

		// 강화 정보 출력 및 사용자 확인
		cout << "아래의 장비를 강화할까요?:\n";
		_Inventory[i]->PrintItemInfo();
		//cout << "[강화: " << UpgradeName << "]\n";
		cout << "--> 현재 강화 레벨 : " << dynamic_cast<Equipment*>(_Inventory[i])->GetEquipmentLevel() << " / 최대 강화 레벨 : " << UPGRADE_MAX_LEVEL << endl;
		cout << "--> 강화 효과 : " << _Inventory[i]->GetTargetStatString() << " +" << UpgradeAmount << " 추가로 증가\n";
		cout << "--> 강화 성공 확률 : " << UpgradeSuccessRate(dynamic_cast<Equipment*>(_Inventory[i])) << "%\n";
		cout << "--> 강화 비용 : " << UpgradeCost << " 골드 (현재 소지 골드: " << character->GetGold() << ")\n" << endl;
		cout << "1: 강화하기 / 0: 상점 메뉴로 돌아가기\n선택: ";

		int Choice;
		cin >> Choice;
		if (Choice == 1)
		{
			// 골드 부족하면 패스
			if (character->GetGold() < UpgradeCost)
			{
				cout << "\n골드가 부족합니다!\n";
				Sleep(500);
				continue;
			}

			// 최대 레벨 도달했으면 패스
			if (dynamic_cast<Equipment*>(_Inventory[i])->GetEquipmentLevel() >= UPGRADE_MAX_LEVEL)
			{
				cout << "\n장비가 최대 레벨에 도달했습니다!\n";
				Sleep(500);
				continue;
			}

			// 종류별 강화 함수 호출
			switch (ID)
			{
			case SWORD:
				// 강화 비용 지출
				character->IncreaseStat(GOLD, UpgradeCost * -1);
				UpgradeEquipment(dynamic_cast<Equipment*>(_Inventory[i]), i);
				cout << "\n상점 메뉴로 돌아갑니다.\n";
				Sleep(500);
				return;

			case ARMOR:
				// 강화 비용 지출
				character->IncreaseStat(GOLD, UpgradeCost * -1);
				UpgradeEquipment(dynamic_cast<Equipment*>(_Inventory[i]), i);
				cout << "\n상점 메뉴로 돌아갑니다.\n";
				Sleep(500);
				return;
			default:
				cout << "\n(로직 오류) 강화 중 강화할 수 없는 아이템을 맞닥뜨렸습니다.\n";
				return;
			}
		}
		else if (Choice == 0)
		{
			cout << "\n상점 메뉴로 돌아갑니다.\n";
			break;
		}
		else
		{
			cout << "\n잘못된 입력입니다.\n";
			Sleep(500);
			continue;
		}
	}
	Sleep(1000);
}

void Shop::UpgradeEquipment(Equipment* equipment, int index)
{
	// 강화할 갑옷을 착용 중인 경우 장착해제
	if (equipment == PInventory->GetEquippedWeapon())
	{
		cout << "\n강화를 위해 장비를 해제합니다.\n";
		PInventory->Unequip(SWORD);
	}
	else if (equipment == PInventory->GetEquippedArmor())
	{
		cout << "\n강화를 위해 장비를 해제합니다.\n";
		PInventory->Unequip(ARMOR);
	}
	
	cout << "\n'*_.,._*^*_.,강화 중,._*^*_.,._*'\n";
	for (int i = 0; i < 8; i++)
	{
		Sleep(1000);
		cout << "...";
	}

	vector<Item*> _Inventory = PInventory->GetInventory();
	if (rand() % 100 < UpgradeSuccessRate(equipment))
	{
		cout << "\n'*,._+-Oo 강화 성공! oO-+.,*^'\n";

		
		if (equipment->GetID() == SWORD)
		{
			_Inventory[index] = new SwordUpgrade(equipment);
		}
		else if (equipment->GetID() == ARMOR)
		{
			_Inventory[index] = new ArmorUpgrade(equipment);
		}
		
		cout << "--> 현재 장비 효과 : " << _Inventory[index]->GetTargetStatString() << " +" << _Inventory[index]->GetStatAmount() << endl;
		cout << "--> 현재 장비 강화 레벨 : " << dynamic_cast<Equipment*>(_Inventory[index])->GetEquipmentLevel() << " / 최대 레벨 : " << UPGRADE_MAX_LEVEL;
	}
	else
	{
		cout << "...강화에 실패하였습니다...다음에는 꼭 성공할테니 너무 상심치 마세요!\n";
	}
	
	PInventory->AutoEquip(_Inventory[index]);
}

// 강화 성공 확률 = 90 - (강화 레벨)*20
int Shop::UpgradeSuccessRate(Equipment* e)
{
	return 90 - e->GetEquipmentLevel() * 20;
}