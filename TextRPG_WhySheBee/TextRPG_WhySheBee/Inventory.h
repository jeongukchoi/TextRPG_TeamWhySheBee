#pragma once
class Inventory
{
private:
	// 아이템 객체 저장
	// 1. 소모품 : 객체를 최초 하나만 저장하고 이후 추가 시 InventoryCount[ItemID] 를 증가시킴
	// 2. 장비 : 추가 시 새로운 객체 생성하여 벡터에 더함
	vector<Item*> _Inventory;
	// 인벤토리 내 아이템 갯수 카운트
	unordered_map<ItemID, int> InventoryCount;
	// 아이템 ID로 아이템을 불러올 ItemManager
	ItemManager _ItemManager;
	// 착용 중인 장비
	Equipment* EquippedItem;

public:
	Inventory();
	~Inventory();
	const vector<Item*>& GetInventory();
	void AddItem(ItemID ID);
	void RemoveItem(ItemID ID, int index);
	void UseItem(ItemID ID);
};

