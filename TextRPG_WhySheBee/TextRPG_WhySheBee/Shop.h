#pragma once
class Shop
{
private:
	ItemManager _ItemManager;
	Inventory* PInventory;
	const int UPGRADE_MAX_LEVEL = 4;
	const int ARMOR_UPGRADE_AMOUNT = 15;
	const int ARMOR_UPGRADE_COST = 150;
	const int SWORD_UPGRADE_AMOUNT = 5;
	const int SWORD_UPGRADE_COST = 200;

public:
	Shop();
	void StartShop();
	void BuyItems();
	void SellItems();
	void UpgradeEquipment();
	void UpgradeEquipment(Equipment* e, int index);
	int UpgradeSuccessRate(Equipment* e);
	void BuyItems();
	void SellItems();
};

