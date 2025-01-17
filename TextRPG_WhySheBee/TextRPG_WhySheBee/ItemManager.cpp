#include "Framework.h"
#include "ItemManager.h"

ItemManager::ItemManager()
{
	ItemsList.push_back(new HealthPotion());
	ItemsList.push_back(new AttackBoost());
	ItemsList.push_back(new UniquePotion());
	ItemsList.push_back(new Sword());
	ItemsList.push_back(new Armor());	
}

ItemManager::~ItemManager()
{
	for (Item* i : ItemsList)
	{
		delete i;
	}
}

Item* ItemManager::GetItem(ItemID ID) const
{
	if (ID < ItemsList.size())
	{
		return ItemsList[ID];
	}
	throw out_of_range("\nItemID 로 아이템을 불러오는 과정에서 문제가 발생했습니다.");
}

ItemID ItemManager::GetRandomItem() const
{
	// 5% 확률로 장비 드랍 (갑옷 70% / 무기 30%)
	int Random = rand() % 100;
	if (Random < 5)
	{
		Random = rand() % 100;
		return Random < 70 ? ARMOR : SWORD;
		
	}
	// 소모품 드랍 (체력 회복 물약 70% / 공격력 증가 물약 20% / 유니크 스탯 물약 10%)
	Random = rand() % 100;
	if (Random < 70)
	{
		return HEALTH_POTION;
	}
	else if (Random < 90)
	{
		return ATTACK_BOOST;
	}
	else
	{
		return UNIQUE_POTION;
	}
}

int ItemManager::GetItemsListSize() const
{
	return ItemsList.size();
}

const vector<Item*>& ItemManager::GetItemsList() const
{
	return ItemsList;
}

void ItemManager::ShowItemDB()
{
	ConsoleManager Console;
	if (ItemsList.empty())
	{
		cout << "*************(오류) 아이템 DB가 비어 있습니다.*************\n";
		Sleep(1000);
		return;
	}

	for (int i = 0; i < ItemsList.size(); i++)
	{
		string ItemString = "[아이템 번호 " + to_string(i + 1) + "]\n" + ItemsList[i]->GetItemInfoString();
		Console.DisplayDialogue(ItemString, i * ITEM_WIDTH, Shop::MENU_NAME_HEIGHT, ITEM_WIDTH, ITEM_HEIGHT, 0, 0);
	}
}

