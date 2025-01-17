#pragma once
#include <vector>
#include <memory>

class ItemManager
{
private:
	vector<Item*> ItemsList;


public:
	/** UI 기본 수치 **/
	static const int ITEM_WIDTH = 23;
	static const int ITEM_HEIGHT = 10;

	ItemManager();
	~ItemManager();
	Item* GetItem(ItemID ID) const;
	ItemID GetRandomItem() const;
	int GetItemsListSize() const;
	const vector<Item*>& GetItemsList() const;
	void ShowItemDB();
};
