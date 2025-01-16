#include "Framework.h"
#include "Shop.h"
#undef max

Shop::Shop()
{
	PInventory = Inventory::GetInstance();
}

// 상점 메뉴 인터페이스
void Shop::StartShop()
{
	Console.ClearConsoleSizeScreen();
	
	// 인삿말 출력 (GREETINGS)
	Console.DisplayDialogue(GREETINGS, 0, WINDOW_HEIGHT - DIALOG_HEIGHT, WINDOW_WIDTH, DIALOG_HEIGHT, OFFSET, OFFSET);
	Sleep(1500);
	Console.ClearConsoleSizeScreen();
	while (true)
	{
		// 상점 기본 메뉴 출력 (SHOP_MENU)
		Console.DisplayDialogue(SHOP_MENU, WINDOW_WIDTH / 2 - CHOICE_WIDTH / 2 - 1, WINDOW_HEIGHT / 2 - CHOICE_HEIGHT / 2 - 1, CHOICE_WIDTH, CHOICE_HEIGHT, OFFSET, OFFSET);
		Console.SetCursorPosition(INPUT_CURSOR_X, INPUT_CURSOR_Y - 1);
		cout << "번호를 입력하세요: ";
		int Choice;
		cin >> Choice;
		switch (Choice)
		{
		case 1:
			Console.ClearConsoleSizeScreen();
			// 아이템 구매
			BuyItems();
			break;

		case 2:
			Console.ClearConsoleSizeScreen();
			// 아이템 판매
			SellItems();
			break;

		case 3:
			Console.ClearConsoleSizeScreen();
			// 아이템 강화
			UpgradeEquipment(); 
			break;

		case 4:
			Console.ClearConsoleSizeScreen();
			// 상점 주인과 차 마시기
			DrinkTea();
			break;
		
		case 0:
			Console.ClearConsoleSizeScreen();
			// 작별인사 출력 (FAREWELL)
			Console.DisplayDialogue(FAREWELL, 0, WINDOW_HEIGHT - DIALOG_HEIGHT, WINDOW_WIDTH, DIALOG_HEIGHT, OFFSET, OFFSET);
			Sleep(1500);
			Console.ClearConsoleSizeScreen();
			return;
		}
		Sleep(1500);
		Console.ClearConsoleSizeScreen();
	}
}

void Shop::BuyItems()
{
	// 인벤토리와 캐릭터 싱글톤 인스턴스 가져오기
	Inventory* inventory = Inventory::GetInstance();
	PlayerCharacter* character = PlayerCharacter::GetPlayer();
	
	// 게임 내 존재하는 아이템 리스트
	ItemManager IM;
	const vector<Item*>& ItemDB = IM.GetItemsList();

	while (true)
	{
		// 구매 메뉴 상단 출력 & 아이템리스트 출력
		const string BUY_MENU = "[아이템 구매]\n(현재 소지 골드 : " + to_string(character->GetGold()) + ")\n0 : 상점 메뉴로 돌아가기";
		Console.ClearConsoleSizeScreen();
		Console.DisplayDialogue(BUY_MENU, 0, 0, WINDOW_WIDTH, MENU_NAME_HEIGHT, OFFSET, 0);
		IM.ShowItemDB();

		// 커서 이동하여 입력 받음
		Console.SetCursorPosition(INPUT_CURSOR_X, INPUT_CURSOR_Y-1);
		cout << "번호를 입력하세요: ";
		int Choice;
		cin >> Choice;
		Choice--;

		if (Choice == -1)
		{
			Console.ClearConsoleSizeScreen();
			Console.DisplayDialogue(RETURN_TO_SHOP, 0, 0, WINDOW_WIDTH, MENU_NAME_HEIGHT, OFFSET, 0);
			return;
		}
		else if (Choice >= 0 && Choice < ItemDB.size())
		{
			if (character->GetGold() < ItemDB[Choice]->GetPrice())
			{
				Console.ClearConsoleSizeScreen();
				const string NOT_ENOUGH_GOLD = "상점 주인: 미안하지만...골드가...모자란 것...같군...\n(현재 소지 골드 : " + to_string(PlayerCharacter::GetPlayer()->GetGold()) + ")";
				Console.DisplayDialogue(NOT_ENOUGH_GOLD, 0, WINDOW_HEIGHT - DIALOG_HEIGHT, WINDOW_WIDTH, DIALOG_HEIGHT, OFFSET, OFFSET);
				Sleep(1500);
				continue;
			}
			cout << endl;
			// 골드 차감 후 인벤토리에 추가
			character->IncreaseStat(GOLD, ItemDB[Choice]->GetPrice() * -1);
			inventory->AddItem(ItemDB[Choice]->GetID()); // AddItem 에서 Sleep(1000) 호출
		}
		else
		{
			Console.ClearConsoleSizeScreen();
			Console.DisplayDialogue(NOT_VALID_INPUT, 0, WINDOW_HEIGHT - DIALOG_HEIGHT, WINDOW_WIDTH, DIALOG_HEIGHT, OFFSET, OFFSET);
			Sleep(1500);
		}
	}
}

void Shop::SellItems()
{
	Inventory* inventory = Inventory::GetInstance();
	PlayerCharacter* character = PlayerCharacter::GetPlayer();

	while (true)
	{
		// 판매 메뉴 상단 출력 & 인벤토리 출력
		const string SELL_MENU = "[아이템 판매]\n(현재 소지 골드 : " + to_string(PlayerCharacter::GetPlayer()->GetGold()) + ")\n0 : 상점 메뉴로 돌아가기";
		Console.ClearConsoleSizeScreen();
		Console.DisplayDialogue(SELL_MENU, 0, 0, WINDOW_WIDTH, MENU_NAME_HEIGHT, OFFSET, 0);
		inventory->ShowInven();

		// 커서 이동하여 입력 받음
		Console.SetCursorPosition(INPUT_CURSOR_X, MENU_NAME_HEIGHT + ItemManager::ITEM_HEIGHT * (inventory->GetInventory().size() / 5 + 1) + 1);
		cout << "번호를 입력하세요: ";
		int choice;
		cin >> choice;
		choice--;

		if (choice == -1)
		{
			Console.ClearConsoleSizeScreen();
			Console.DisplayDialogue(RETURN_TO_SHOP, 0, 0, WINDOW_WIDTH, MENU_NAME_HEIGHT, OFFSET, 0);
			return;
		}
		else if (choice >= 0 && choice < inventory->GetInventory().size())
		{
			Item* item = inventory->GetInventory()[choice];
			string ItemName = item->GetName();
			
			character->IncreaseStat(GOLD, (int) item->GetPrice() * 0.6);
			inventory->RemoveItem(item, choice);

			string SELL_ITEM = ItemName + " 아이템을 판매하였습니다!\n...\n상점 주인: 고맙군요...어딘가에 잘...써보도록...하지요...";
			Console.ClearConsoleSizeScreen();
			Console.DisplayDialogue(SELL_ITEM, 0, WINDOW_HEIGHT - DIALOG_HEIGHT, WINDOW_WIDTH, DIALOG_HEIGHT, OFFSET, OFFSET);
			Sleep(1500);
		}
		else
		{
			Console.ClearConsoleSizeScreen();
			Console.DisplayDialogue(NOT_VALID_INPUT, 0, WINDOW_HEIGHT - DIALOG_HEIGHT, WINDOW_WIDTH, DIALOG_HEIGHT, OFFSET, OFFSET);
			Sleep(1500);
		}
	}
}

void Shop::DrinkTea()
{
	Console.ClearConsoleSizeScreen();
	Console.DisplayDialogue("......차 마시는 중......", WINDOW_WIDTH / 2 - CHOICE_WIDTH / 2 - 1, WINDOW_HEIGHT / 2 - CHOICE_HEIGHT / 2 - 1, CHOICE_WIDTH, CHOICE_HEIGHT, OFFSET, OFFSET);
	int CurrX = WINDOW_WIDTH / 2 - CHOICE_WIDTH / 2 + OFFSET;
	for (int i = 0; i < 6; i++)
	{
		Console.SetCursorPosition(CurrX, WINDOW_HEIGHT / 2 - CHOICE_HEIGHT / 2 + OFFSET + 3);
		cout << "...홀짝";
		CurrX += 7;
		Sleep(1500);
	}
	Console.SetCursorPosition(WINDOW_WIDTH / 2 - CHOICE_WIDTH / 2 + OFFSET, WINDOW_HEIGHT / 2 - CHOICE_HEIGHT / 2 + OFFSET + 4);
	string AFTER_TEA = "(몸에 따뜻한 기운이 퍼진다. \n 주인과 이런저런 이야기를 나누며 마음이 편안해졌다.)";
	Console.DisplayDialogue(AFTER_TEA, 0, WINDOW_HEIGHT - DIALOG_HEIGHT, WINDOW_WIDTH, DIALOG_HEIGHT, OFFSET, OFFSET);
}

void Shop::UpgradeEquipment()
{
	PlayerCharacter* character = PlayerCharacter::GetPlayer();
	const vector<Item*>& _Inventory = PInventory->GetInventory();

	while(true)
	{
		// 판매 메뉴 상단 출력 & 인벤토리 출력
		const string UPGRADE_MENU = "[아이템 강화]\n(현재 소지 골드 : " + to_string(PlayerCharacter::GetPlayer()->GetGold()) + ")\n0 : 상점 메뉴로 돌아가기";
		Console.ClearConsoleSizeScreen();
		Console.DisplayDialogue(UPGRADE_MENU, 0, 0, WINDOW_WIDTH, MENU_NAME_HEIGHT, OFFSET, 0);
		PInventory->ShowInven();

		// 커서 이동하여 입력 받음
		Console.SetCursorPosition(INPUT_CURSOR_X, MENU_NAME_HEIGHT + ItemManager::ITEM_HEIGHT * (_Inventory.size() / 5 + 1) + 1);
		cout << "번호를 입력하세요: ";
		int i;
		cin >> i;
		i--;

		if (i == -1)
		{
			Console.ClearConsoleSizeScreen();
			Console.DisplayDialogue(RETURN_TO_SHOP, 0, 0, WINDOW_WIDTH, MENU_NAME_HEIGHT, OFFSET, 0);
			return;
		}

		if (i < 0 || i >= _Inventory.size())
		{
			Console.ClearConsoleSizeScreen();
			Console.DisplayDialogue(NOT_VALID_INPUT, 0, WINDOW_HEIGHT - DIALOG_HEIGHT, WINDOW_WIDTH, DIALOG_HEIGHT, OFFSET, OFFSET);
			Sleep(1500);
			continue;
		}

		// 장비 아닌 아이템
		if (_Inventory[i]->GetType() != EQUIPMENT)
		{
			Console.ClearConsoleSizeScreen();
			Console.DisplayDialogue(NOT_EQUIPMENT, 0, WINDOW_HEIGHT - DIALOG_HEIGHT, WINDOW_WIDTH, DIALOG_HEIGHT, OFFSET, OFFSET);
			Sleep(1500);
			continue;
		}

		// 강화 정보를 반환하기 위한 임시 값들
		int UpgradeAmount;
		int UpgradeCost;
		ItemID ID = _Inventory[i]->GetID();

		string UpgradeName = GetUpgradeName(ID, dynamic_cast<Equipment*>(_Inventory[i])->GetEquipmentLevel());
		if (ID == ARMOR)
		{
			UpgradeAmount = dynamic_cast<Equipment*>(_Inventory[i])->GetUpgradeAmount() + ARMOR_UPGRADE_AMOUNT;
			UpgradeCost = dynamic_cast<Equipment*>(_Inventory[i])->GetUpgradeCost() + ARMOR_UPGRADE_COST;
		}
		else if (ID == SWORD)
		{
			UpgradeAmount = dynamic_cast<Equipment*>(_Inventory[i])->GetUpgradeAmount() + SWORD_UPGRADE_AMOUNT;
			UpgradeCost = dynamic_cast<Equipment*>(_Inventory[i])->GetUpgradeCost() + SWORD_UPGRADE_COST;
		}
		else
		{
			throw runtime_error("----강화 중 유효하지 않은 ID가 발견되었습니다.");
		}

		// 강화 정보 출력 및 사용자 확인
		const string UPGRADE_CONFIRM = "아래의 장비를 강화할까요?:\n" + _Inventory[i]->GetItemInfoString()
			+ "\n \n[강화: " + UpgradeName + "]\n"
			+ "\n--> 현재 강화 레벨 : " + to_string(dynamic_cast<Equipment*>(_Inventory[i])->GetEquipmentLevel()) + " / 최대 강화 레벨 : " + to_string(UPGRADE_MAX_LEVEL)
			+ "\n--> 강화 효과 : " + _Inventory[i]->GetTargetStatString() + " +" + to_string(UpgradeAmount) + " 추가로 증가"
			+ "\n--> 강화 성공 확률 : " + to_string(UpgradeSuccessRate(dynamic_cast<Equipment*>(_Inventory[i]))) + "%"
			+ "\n--> 강화 비용 : " + to_string(UpgradeCost) + " 골드 (현재 소지 골드: " + to_string(character->GetGold()) + ")"
			+ "\n1: 강화하기 / 0: 상점 메뉴로 돌아가기";
		Console.ClearConsoleSizeScreen();
		Console.DisplayDialogue(UPGRADE_CONFIRM, WINDOW_WIDTH / 2 - CHOICE_WIDTH / 2 - 1, WINDOW_HEIGHT / 2 - (CHOICE_HEIGHT + 2) / 2 - 1, CHOICE_WIDTH, CHOICE_HEIGHT + 2, OFFSET, 0);

		// 커서 이동하여 입력 받기
		Console.SetCursorPosition(INPUT_CURSOR_X, INPUT_CURSOR_Y - 1);
		cout << "번호를 입력하세요: ";
		int Choice;
		cin >> Choice;

		// 강화 진행
		if (Choice == 1)
		{
			// 골드 부족하면 패스
			if (character->GetGold() < UpgradeCost)
			{
				Console.ClearConsoleSizeScreen();
				const string NOT_ENOUGH_GOLD = "상점 주인: 미안하지만...골드가...모자란 것...같군...\n(현재 소지 골드 : " + to_string(PlayerCharacter::GetPlayer()->GetGold()) + ")";
				Console.DisplayDialogue(NOT_ENOUGH_GOLD, 0, WINDOW_HEIGHT - DIALOG_HEIGHT, WINDOW_WIDTH, DIALOG_HEIGHT, OFFSET, OFFSET);
				Sleep(1500);
				continue;
			}

			// 최대 레벨 도달했으면 패스
			if (dynamic_cast<Equipment*>(_Inventory[i])->GetEquipmentLevel() >= UPGRADE_MAX_LEVEL)
			{
				Console.ClearConsoleSizeScreen();
				Console.DisplayDialogue(EQUIPMENT_MAX_LEVEL, 0, WINDOW_HEIGHT - DIALOG_HEIGHT, WINDOW_WIDTH, DIALOG_HEIGHT, OFFSET, OFFSET);
				Sleep(1500);
				continue;
			}

			// 종류별 강화 함수 호출
			switch (ID)
			{
			case SWORD:
				// 강화 비용 지출
				character->IncreaseStat(GOLD, UpgradeCost * -1);
				UpgradeEquipment(dynamic_cast<Equipment*>(_Inventory[i]), i);
				return;

			case ARMOR:
				// 강화 비용 지출
				character->IncreaseStat(GOLD, UpgradeCost * -1);
				UpgradeEquipment(dynamic_cast<Equipment*>(_Inventory[i]), i);
				return;
			default:
				Console.ClearConsoleSizeScreen();
				cout << "\n(로직 오류) 강화 중 강화할 수 없는 아이템을 맞닥뜨렸습니다.\n";
				Sleep(1500);
				return;
			}
		}

		// 상점 돌아가기
		else if (Choice == 0)
		{
			Console.ClearConsoleSizeScreen();
			Console.DisplayDialogue(RETURN_TO_SHOP, 0, 0, WINDOW_WIDTH, MENU_NAME_HEIGHT, OFFSET, 0);
			return;
		}

		// 유효하지 않은 입력
		else
		{
			Console.ClearConsoleSizeScreen();
			Console.DisplayDialogue(NOT_VALID_INPUT, 0, WINDOW_HEIGHT - DIALOG_HEIGHT, WINDOW_WIDTH, DIALOG_HEIGHT, OFFSET, OFFSET);
			Sleep(1500);
			continue;
		}
	}
	Sleep(1500);
}

void Shop::UpgradeEquipment(Equipment* equipment, int index)
{
	// 강화할 갑옷을 착용 중인 경우 장착해제
	if (equipment == PInventory->GetEquippedWeapon())
	{
		PInventory->Unequip(SWORD);
	}
	else if (equipment == PInventory->GetEquippedArmor())
	{
		PInventory->Unequip(ARMOR);
	}
	
	Console.ClearConsoleSizeScreen();
	Console.DisplayDialogue("\n'*_.,._*^*_.,강화 중,._*^*_.,._*'\n", WINDOW_WIDTH / 2 - CHOICE_WIDTH / 2 - 1, WINDOW_HEIGHT / 2 - CHOICE_HEIGHT / 2 - 1, CHOICE_WIDTH, CHOICE_HEIGHT, OFFSET, OFFSET);
	int CurrX = WINDOW_WIDTH / 2 - CHOICE_WIDTH / 2 + OFFSET;
	
	for (int i = 0; i < 6; i++)
	{
		Console.SetCursorPosition(CurrX, WINDOW_HEIGHT / 2 - CHOICE_HEIGHT / 2 + OFFSET + 3);
		cout << "...깡";
		CurrX += 5;
		Sleep(1500);
	}

	const vector<Item*>& _Inventory = PInventory->GetInventory();
	string UPGRADE_RESULT;
	if (rand() % 100 < UpgradeSuccessRate(equipment))
	{
		if (equipment->GetID() == SWORD)
		{
			equipment = new SwordUpgrade(equipment);
			PInventory->ReplaceItem(equipment, index);
		}
		else if (equipment->GetID() == ARMOR)
		{
			equipment = new ArmorUpgrade(equipment);
			PInventory->ReplaceItem(equipment, index);
		}
		UPGRADE_RESULT = "'*,._+-Oo 강화 성공! oO-+.,*^'\n--> 현재 장비 효과 : " + _Inventory[index]->GetTargetStatString() + " +" + to_string(_Inventory[index]->GetStatAmount())
			+ "\n--> 현재 장비 강화 레벨 : " + to_string(dynamic_cast<Equipment*>(_Inventory[index])->GetEquipmentLevel()) + " / 최대 레벨 : " + to_string(UPGRADE_MAX_LEVEL);
	}
	else
	{
		UPGRADE_RESULT = "상점 주인: 어이쿠...손이...미끄러져서...다음에는 꼭...성공할게요...죄송해요...\n(강화에 실패했습니다...)";
	}
	Console.DisplayDialogue(UPGRADE_RESULT, 0, WINDOW_HEIGHT - DIALOG_HEIGHT, WINDOW_WIDTH, DIALOG_HEIGHT, OFFSET, OFFSET);
	Sleep(1500);
	PInventory->AutoEquip(_Inventory[index]);
}

// 강화 성공 확률 = 90 - (강화 레벨)*20
int Shop::UpgradeSuccessRate(Equipment* e)
{
	return 90 - e->GetEquipmentLevel() * 20;
}

string Shop::GetUpgradeName(ItemID ID, int Level)
{
	if (ID == ARMOR)
	{
		switch (Level)
		{
		case 0:
			return "무두질";

		case 1:
			return "이음새 강화";

		case 2:
			return "안감 덧대기";

		case 3:
			return "표면 금속 코팅";
		}
	}
	else if (ID == SWORD)
	{
		switch (Level)
		{
		case 0:
			return "칼날 다듬기";

		case 1:
			return "손잡이 경량화";

		case 2:
			return "장인의 특별 개조";

		case 3:
			return "아다만티움 코팅";
		}
	}
	return "";
}