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
	Equipment* EquippedWeapon;
	Equipment* EquippedArmor;

	// 인벤토리의 싱글톤 인스턴스
	static Inventory* Instance;
	// 프라이빗 생성자 & 소멸자
	Inventory();
	~Inventory();
	// 복사 및 대입 생성자 삭제
	Inventory(const Inventory&) = delete;
	Inventory& operator=(const Inventory&) = delete;

public:
	static Inventory* GetInstance();
	const vector<Item*>& GetInventory();
	Item* GetEquippedWeapon() { return EquippedWeapon; }
	Item* GetEquippedArmor() { return EquippedArmor; }
	void AddItem(ItemID ID);
	void RemoveItem(Item* item, int index);
	void UseItem(Item* item);
	void ReplaceItem(Item* item, int index);
	void UseConsumables();
	void Unequip(ItemID ID);
	void AutoEquip(Item* item);
	void ShowInven();
};

