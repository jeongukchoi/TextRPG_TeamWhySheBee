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
	ItemID GetRandomItem() const;
	int GetItemsListSize() const;
	const vector<Item*>& GetItemsList() const;
	void ShowItemDB();
};
