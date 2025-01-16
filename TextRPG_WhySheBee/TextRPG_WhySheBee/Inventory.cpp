#include "Framework.h"
#include "Inventory.h"

// 정적 멤버 변수 초기화
Inventory* Inventory::Instance = nullptr;

Inventory::Inventory() : _Inventory({}), InventoryCount({}), EquippedWeapon(nullptr), EquippedArmor(nullptr)
{
}

Inventory::~Inventory()
{
	for (Item* item : _Inventory)
	{
		delete item;
	}
}

Inventory* Inventory::GetInstance()
{
	if (Instance == nullptr)
	{
		Instance = new Inventory();
	}
	return Instance;
}

const vector<Item*>& Inventory::GetInventory()
{
	return _Inventory;
}

void Inventory::AddItem(ItemID ID)
{
	Item* ItemFromDB = _ItemManager.GetItem(ID);
	ItemType Type = ItemFromDB->GetType();
	
	string AddItemString = "._*^아이템 획득^*_.\n" + ItemFromDB->GetItemInfoString();
	Console.ClearConsoleSizeScreen();
	Console.DisplayDialogue(AddItemString, 0, Shop::WINDOW_HEIGHT - Shop::DIALOG_HEIGHT, Shop::WINDOW_WIDTH, Shop::DIALOG_HEIGHT, Shop::OFFSET, Shop::OFFSET);
	Sleep(1000);
	// 추가할 아이템이 소모품인 경우
	if (Type == CONSUMABLES)
	{
		// 인벤토리에 해당 아이템이 없는 경우 객체 생성 후 추가
		if (InventoryCount.find(ID) == InventoryCount.end()) {
			switch (ID)
			{
			case HEALTH_POTION:
				_Inventory.push_back(new HealthPotion());
				break;

			case ATTACK_BOOST:
				_Inventory.push_back(new AttackBoost());
				break;

			case UNIQUE_POTION:
				_Inventory.push_back(new UniquePotion());
				break;

			default:
				cout << "\n(오류) 아이템 ID가 유효하지 않아 인벤토리에 추가하지 못했습니다.\n";
				break;
			}
		}
		// 카운트 증가
		InventoryCount[ID]++;
	}

	// 추가할 아이템이 장비인 경우
	else if (Type == EQUIPMENT)
	{
		switch (ID)
		{
		case SWORD:
			_Inventory.push_back(new Sword());
			AutoEquip(_Inventory.back());
			break;

		case ARMOR:
			_Inventory.push_back(new Armor());
			AutoEquip(_Inventory.back());
			break;

		default:
			cout << "\n(오류) 아이템 ID가 유효하지 않아 인벤토리에 추가하지 못했습니다.\n";
			break;
		}
	}
	Console.ClearConsoleSizeScreen();
}

void Inventory::RemoveItem(Item* item, int index)
{	
	if (item == nullptr)
	{
		throw runtime_error("\n---------인벤토리에서 아이템을 제거하는 중 인덱스 오류 발생\n");
	}

	ItemID ID = item->GetID();
	ItemType Type = item->GetType();
	
	// 제거할 아이템이 소모품인 경우
	if (Type == CONSUMABLES)
	{
		// 인벤토리에 해당 아이템이 존재하는 경우
		if (InventoryCount.find(ID) != InventoryCount.end() && InventoryCount.find(ID)->second > 0) {
			// 카운트 감소
			InventoryCount[ID]--;
			if (InventoryCount[ID] == 0)
			{
				auto InventoryPos = find_if(_Inventory.begin(), _Inventory.end(), [ID](Item* i) {
					return i->GetID() == ID;
				});
				auto CountPos = InventoryCount.find(ID);
				_Inventory.erase(InventoryPos);
				InventoryCount.erase(CountPos);
			}
		}
		return;
	}

	// 제거할 아이템이 장비인 경우
	if (ID == SWORD)
	{
		// 착용 중인 경우 장착 해제
		if (EquippedWeapon == item)
		{
			Unequip(SWORD);
		}
	}
	else if (ID == ARMOR)
	{
		// 착용 중인 경우 장착 해제
		if (EquippedArmor == item)
		{
			Unequip(ARMOR);
		}
	}
	
	if (_Inventory[index]->GetID() != ID)
	{
		throw runtime_error("\n-------RemoveItem 인자로 받은 인덱스가 잘못된 객체를 가리키고 있음");
	}
	delete item;
	_Inventory.erase(_Inventory.begin() + index);
}

void Inventory::UseItem(Item* item)
{
	ItemID ID = item->GetID();
	ItemType Type = item->GetType();
	string Name = item->GetName();

	// 소모품인 경우 사용 후 인벤토리에서 삭제
	if (Type == CONSUMABLES)
	{
		auto InventoryIt = InventoryCount.find(ID);
		if (InventoryIt != InventoryCount.end() && InventoryIt->second > 0)
		{
			item->Use();
			RemoveItem(item, 0);
		}
		return;
	}

	// 장비인 경우 착용 중인 장비 해제 후 해당 장비 착용
	if (Type == EQUIPMENT)
	{
		Equipment* equipment = dynamic_cast<Equipment*>(item);
		switch (ID)
		{
		case SWORD:
			// 현재 장비 해제 후 아이템 사용
			Unequip(SWORD);
			item->Use();
			EquippedWeapon = equipment;
			break;

		case ARMOR:
			Unequip(ARMOR);
			item->Use();
			EquippedArmor = equipment;
			break;
		}

		Console.ClearConsoleSizeScreen();
		string EquipItemString = "._*oO@-아이템 장착-@Oo*_.\n" + equipment->GetItemInfoString();
		Console.DisplayDialogue(EquipItemString, 0, Shop::WINDOW_HEIGHT - Shop::DIALOG_HEIGHT, Shop::WINDOW_WIDTH, Shop::DIALOG_HEIGHT, Shop::OFFSET, Shop::OFFSET);
	}
	Sleep(1000);
}

void Inventory::ReplaceItem(Item* item, int index)
{
	if (item != nullptr && index >= 0 && index < _Inventory.size())
	{
		_Inventory[index] = item;
	}
}

string Inventory::UseConsumables()
{
	for (Item* item : _Inventory)
	{
		if (item->GetType() == CONSUMABLES && InventoryCount[item->GetID()] > 0)
		{
			string ItemString = item->GetName() + " 아이템을 사용하였습니다.";
			UseItem(_ItemManager.GetItem(item->GetID()));
			return ItemString;
		}
	}
	return "";
}

void Inventory::Unequip(ItemID ID)
{
	PlayerCharacter* character = PlayerCharacter::GetPlayer();
	switch (ID)
	{
	case SWORD:
		if (EquippedWeapon != nullptr)
		{
			string UnequipItemString = "착용중인 무기가 해제되었습니다.";
			Console.ClearConsoleSizeScreen();
			Console.DisplayDialogue(UnequipItemString, 0, Shop::WINDOW_HEIGHT - Shop::DIALOG_HEIGHT, Shop::WINDOW_WIDTH, Shop::DIALOG_HEIGHT, Shop::OFFSET, Shop::OFFSET);
			// 장비 효과 해제
			character->IncreaseStat(EquippedWeapon->GetTargetStat(), EquippedWeapon->GetTargetStat() * -1);
			EquippedWeapon = nullptr;
			Sleep(1000);
		}
		break;
	case ARMOR:
		if (EquippedArmor != nullptr)
		{
			string UnequipItemString = "착용중인 갑옷이 해제되었습니다.";
			Console.ClearConsoleSizeScreen();
			Console.DisplayDialogue(UnequipItemString, 0, Shop::WINDOW_HEIGHT - Shop::DIALOG_HEIGHT, Shop::WINDOW_WIDTH, Shop::DIALOG_HEIGHT, Shop::OFFSET, Shop::OFFSET);
			// 장비 효과 해제
			character->IncreaseStat(EquippedArmor->GetTargetStat(), EquippedArmor->GetTargetStat() * -1);
			EquippedArmor = nullptr;
			Sleep(1000);
		}
		break;
	}
}

void Inventory::AutoEquip(Item* item)
{
	// 현재 착용 중인 장비가 없으면 바로 착용
	// 있으면 증가 스탯 비교하여 높으면 새로운 장비 착용
	switch (item->GetID())
	{
		Console.ClearConsoleSizeScreen();

	case SWORD:
		if (EquippedWeapon == nullptr)
		{
			UseItem(item);
		}
		else
		{
			if (EquippedWeapon->GetStatAmount() < item->GetStatAmount())
			{
				UseItem(item);
			}
		}
		break;

	case ARMOR:
		if (EquippedArmor == nullptr)
		{
			UseItem(item);
		}
		else
		{
			if (EquippedArmor->GetStatAmount() < item->GetStatAmount())
			{
				UseItem(item);
			}
		}
		break;
	}
}

void Inventory::ShowInven()
{
	if (_Inventory.empty())
	{
		string InventoryEmpty = "*************인벤토리가 비어 있습니다.*************";
		Console.DisplayDialogue(InventoryEmpty, 0, Shop::WINDOW_HEIGHT - Shop::DIALOG_HEIGHT, Shop::WINDOW_WIDTH, Shop::DIALOG_HEIGHT, Shop::OFFSET, Shop::OFFSET);
		Sleep(1000);
		return;
	}

	for (int i = 0; i < _Inventory.size(); i++)
	{
		string ItemString = "[아이템 번호 " + to_string(i + 1) + "]\n이름: " + _Inventory[i]->GetName();
		// 소모품의 경우 갯수 / 장비의 경우 강화 레벨
		if (_Inventory[i]->GetType() == CONSUMABLES)
		{
			ItemString += "\n개수: " + to_string(InventoryCount[_Inventory[i]->GetID()]);
		}
		else if (_Inventory[i]->GetType() == EQUIPMENT)
		{
			if (EquippedArmor == _Inventory[i] || EquippedWeapon == _Inventory[i])
			{
				ItemString += "\n**장착중**";
			}
			ItemString += "\n강화 레벨: " + to_string(dynamic_cast<Equipment*>(_Inventory[i])->GetEquipmentLevel());
		}
		ItemString += "\n판매가: " + to_string(static_cast<int>(_Inventory[i]->GetPrice() * 0.6));

		Console.DisplayDialogue(ItemString, (i % 5) * ItemManager::ITEM_WIDTH, Shop::MENU_NAME_HEIGHT + ItemManager::ITEM_HEIGHT * (i / 5), ItemManager::ITEM_WIDTH, ItemManager::ITEM_HEIGHT, 0, 0);
	}
}

