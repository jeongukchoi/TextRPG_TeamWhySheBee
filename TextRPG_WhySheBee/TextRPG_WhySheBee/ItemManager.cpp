#include "Framework.h"
#include "ItemManager.h"

ItemManager::ItemManager()
{
	ItemsList.push_back(new HealthPotion());
	ItemsList.push_back(new AttackBoost());
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

Item* ItemManager::GetRandomItem() const
{
	if (!ItemsList.empty())
	{
		return ItemsList[rand() % ItemsList.size()];
	}
	throw out_of_range("\n랜덤 아이템을 불러오는 과정에서 문제가 발생했습니다.");
}

