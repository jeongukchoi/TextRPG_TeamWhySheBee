#pragma once
#include <vector>

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

