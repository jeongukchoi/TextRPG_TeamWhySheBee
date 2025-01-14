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

	cout << "\n._*^아이템 획득^*_.\n";
	ItemFromDB->PrintItemInfo();

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

			default:
				cout << "\n아이템 ID가 유효하지 않아 인벤토리에 추가하지 못했습니다.\n";
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
			break;
		}
	}
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

			cout << "\n^*._아이템 제거_.*^\n\n" << item->GetName() << " 아이템이 인벤토리에서 제거되었습니다.\n\n";
			return;
		}
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
	cout << "\n^*._아이템 제거_.*^\n" << item->GetName() << "아이템이 인벤토리에서 제거되었습니다.\n\n";
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
			cout << "\n._*oO@-아이템 사용-@Oo*_.\n\n" << item->GetName() << " 아이템이 사용되었습니다.\n";
			item->PrintItemInfo();

			item->Use();
			RemoveItem(item, 0);
		}
		else
		{
			cout << endl << Name << " 아이템을 보유하고 있지 않아 사용하지 못했습니다.\n";
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
		cout << "\n._*oO@-아이템 장착-@Oo*_.\n\n";
		cout << equipment->GetName() << "(+" << equipment->GetEquipmentLevel() << ") 장비를 착용했습니다." << endl;
		equipment->PrintItemInfo();
	}
}

void Inventory::UseConsumables()
{
	for (Item* item : _Inventory)
	{
		if (item->GetType() == CONSUMABLES && InventoryCount[item->GetID()] > 0)
		{
			UseItem(_ItemManager.GetItem(item->GetID()));
		}
	}
}

void Inventory::Unequip(ItemID ID)
{
	PlayerCharacter* character = PlayerCharacter::GetPlayer();
	switch (ID)
	{
	case SWORD:
		if (EquippedWeapon != nullptr)
		{
			cout << "\n착용중인 무기가 해제되었습니다.\n";
			// 장비 효과 해제
			character->IncreaseStat(EquippedWeapon->GetTargetStat(), EquippedWeapon->GetTargetStat() * -1);
			EquippedWeapon = nullptr;
		}
	case ARMOR:
		if (EquippedArmor != nullptr)
		{
			cout << "\n착용중인 갑옷이 해제되었습니다.\n";
			// 장비 효과 해제
			character->IncreaseStat(EquippedArmor->GetTargetStat(), EquippedArmor->GetTargetStat() * -1);
			EquippedArmor = nullptr;
		}
	}
}

void Inventory::AutoEquip(Item* item)
{
	// 현재 착용 중인 장비가 없으면 바로 착용
	// 있으면 증가 스탯 비교하여 높으면 새로운 장비 착용
	switch (item->GetID())
	{
	case SWORD:
		if (EquippedWeapon == nullptr)
		{
			cout << endl << item->GetName() << " 아이템을 자동으로 장착합니다.\n";
			UseItem(item);
		}
		else
		{
			if (EquippedWeapon->GetStatAmount() < item->GetStatAmount())
			{
				cout << endl << item->GetName() << " 아이템을 자동으로 장착합니다.\n";
				UseItem(item);
			}
		}
		break;

	case ARMOR:
		if (EquippedArmor == nullptr)
		{
			cout << endl << item->GetName() << " 아이템을 자동으로 장착합니다.\n";
			UseItem(item);
		}
		else
		{
			if (EquippedArmor->GetStatAmount() < item->GetStatAmount())
			{
				cout << endl << item->GetName() << " 아이템을 자동으로 장착합니다.\n";
				UseItem(item);
			}
		}
		break;
	}
}

