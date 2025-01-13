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
	ItemID ID = item->GetID();
	ItemType Type = item->GetType();
	// 제거할 아이템이 소모품인 경우
	if (Type == CONSUMABLES)
	{
		// 인벤토리에 해당 아이템이 존재하는 경우
		if (InventoryCount.find(ID) != InventoryCount.end() && InventoryCount.find(ID)->second > 0) {
			// 카운트 감소
			InventoryCount[ID]--;
		}
	}

	// 제거할 아이템이 무기인 경우 (SellItem() 통해서만 제거됨 -> 인덱스 알 수 있음)
	else if (ID == SWORD)
	{
		// 인덱스로 인벤토리에서 장비를 제거
		if (index > _Inventory.size())
		{
			throw out_of_range("\n-----------인벤토리에서 아이템을 제거하는 중 오류가 발생하였습니다.\n");
		}
		
		// 착용 중인 경우
		if (EquippedWeapon == item)
		{
			Unequip(item);
		}

		if (_Inventory[index]->GetType() == EQUIPMENT)
		{
			delete _Inventory[index];
			_Inventory.erase(_Inventory.begin() + index);
		}
		else
		{
			cout << "\n제거할 아이템의 종류와 인벤토리 내 아이템의 종류가 일치하지 않습니다.\n";
		}
	}
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
		else
		{
			cout << endl << Name << " 아이템을 보유하고 있지 않아 사용하지 못했습니다.\n";
		}
		return;
	}

	// 장비인 경우 착용 중인 장비 해제 후 해당 장비 착용
	if (Type == EQUIPMENT)
	{
		switch (ID)
		{
		case SWORD:
			// 현재 장비 해제 후 아이템 사용
			Unequip(EquippedWeapon);
			item->Use();
			EquippedWeapon = reinterpret_cast<Equipment*>(item);
			break;

		case ARMOR:
			Unequip(EquippedArmor);
			item->Use();
			EquippedArmor = reinterpret_cast<Equipment*>(item);
			break;
		}

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



void Inventory::Unequip(Item* item)
{
	PlayerCharacter* character = PlayerCharacter::GetPlayer();
	switch (item->GetID())
	{
	case SWORD:
		if (EquippedWeapon != nullptr)
		{
			// 장비 효과 해제
			character->IncreaseStat(EquippedWeapon->GetTargetStat(), EquippedWeapon->GetTargetStat() * -1);

			EquippedWeapon = nullptr;
		}
	case ARMOR:
		if (EquippedArmor != nullptr)
		{
			// 장비 효과 해제
			character->IncreaseStat(EquippedArmor->GetTargetStat(), EquippedArmor->GetTargetStat() * -1);
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

