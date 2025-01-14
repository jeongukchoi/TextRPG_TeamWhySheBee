#pragma once
class Shop
{
private:
	ItemManager _ItemManager;

public:
	void UpgradeEquipment();
	void UpgradeSword(Equipment* e, PlayerCharacter* character);
	void UpgradeArmor(Equipment* e, PlayerCharacter* character);
	int UpgradeSuccessRate(Equipment* e);
	void BuyItems();
	void SellItems();
};

