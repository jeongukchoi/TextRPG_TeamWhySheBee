#include "Framework.h"
#include "Inventory.h"

Inventory::Inventory() : _Inventory({}), InventoryCount({}), EquippedItem(nullptr)
{
}

Inventory::~Inventory()
{
	for (Item* item : _Inventory)
	{
		delete item;
	}
}

const vector<Item*>& Inventory::GetInventory()
{
	return _Inventory;
}

void Inventory::AddItem(ItemID ID)
{
	ItemType Type = _ItemManager.GetItem(ID)->GetType();
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
			break;

		case ARMOR:
			_Inventory.push_back(new Armor());
			break;

		default:
			break;
		}
	}
}

void Inventory::RemoveItem(ItemID ID, int index)
{	
	Item* ItemByID = _ItemManager.GetItem(ID);
	ItemType Type = ItemByID->GetType();
	// 제거할 아이템이 소모품인 경우
	if (Type == CONSUMABLES)
	{
		// 인벤토리에 해당 아이템이 존재하는 경우
		if (InventoryCount.find(ID) != InventoryCount.end() && InventoryCount.find(ID)->second > 0) {
			// 카운트 감소
			InventoryCount[ID]--;
		}
	}

	// 제거할 아이템이 장비인 경우
	else if (Type == EQUIPMENT)
	{
		// 인덱스로 인벤토리에서 장비를 제거
		if (index > _Inventory.size())
		{
			throw out_of_range("\n-----------인벤토리에서 아이템을 제거하는 중 오류가 발생하였습니다.\n");
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

void Inventory::UseItem(ItemID ID)
{
	Item* ItemByID = _ItemManager.GetItem(ID);
	string Name = ItemByID->GetName();
	ItemType Type = ItemByID->GetType();

	// 소모품인 경우 사용 후 인벤토리에서 삭제
	if (Type == CONSUMABLES)
	{
		auto InventoryIt = InventoryCount.find(ID);
		if (InventoryIt != InventoryCount.end() && InventoryIt->second > 0)
		{
			ItemByID->Use();
			RemoveItem(ID, 0);
		}
		else
		{
			cout << endl << Name << " 아이템을 보유하고 있지 않아 사용하지 못했습니다.\n";
		}
	}

	// 장비인 경우 착용 중인 장비 해제 후 해당 장비 착용
	else if (Type == EQUIPMENT)
	{
		for (int i = 0; i < _Inventory.size(); i++)
		{
			if (_Inventory[i]->GetName() == Name)
			{
				cout << "\n아래 아이템을 착용하려면 1을 입력하세요.";
				_Inventory[i]->PrintItemInfo();
				cout << "1: 착용 / (다른 입력 시 계속해서 인벤토리 내에 같은 아이템을 찾습니다.)\n입력: ";

				int Choice;
				cin >> Choice;

				if (Choice == 1)
				{
					// 현재 장비 해제 구현
					//UnEquip();
					_Inventory[i]->Use();
				}
			}
		}
	}
}


