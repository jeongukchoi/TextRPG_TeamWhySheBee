#include "Framework.h"
#include "ItemManager.h"

ItemManager::ItemManager()
{
	ItemsList.push_back(new HealthPotion());
	ItemsList.push_back(new AttackBoost());
	srand(time(NULL));
}

ItemManager::~ItemManager()
{
	for (Item* i : ItemsList)
	{
		delete i;
	}
}

Item* ItemManager::GetItem(ItemID ID)
{
	if (ID < ItemsList.size())
	{
		cout << ItemsList[ID] << endl;
		return ItemsList[ID];
	}
	cout << "아이템 ID가 유효하지 않습니다. nullptr 반환합니다.\n";
	return nullptr;
}

Item* ItemManager::GetRandomItem()
{
	return ItemsList[rand() % ItemsList.size()];
}