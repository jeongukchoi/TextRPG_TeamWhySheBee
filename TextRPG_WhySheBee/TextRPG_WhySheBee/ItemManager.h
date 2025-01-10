#pragma once
#include <vector>

enum ItemID {
	HEALTH_POTION = 0,
	ATTACK_BOOST
};

class ItemManager
{
private:
	vector<Item*> ItemsList;

public:
	ItemManager();
	~ItemManager();
	Item* GetItem(ItemID ID);
	Item* GetRandomItem();
};

