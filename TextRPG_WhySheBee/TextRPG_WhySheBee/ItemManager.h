#pragma once
#include <vector>
#include <memory>

class ItemManager
{
private:
	vector<Item*> ItemsList;

public:
	ItemManager();
	~ItemManager();
	Item* GetItem(ItemID ID) const;
	Item* GetRandomItem() const;
};


