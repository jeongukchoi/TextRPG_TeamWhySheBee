#pragma once
class Equipment : public Item
{
public:
	virtual ~Equipment() {}
	// 장비 강화 레벨
	virtual int GetEquipmentLevel() const = 0;
	// 장비 해제
	virtual int GetUpgradeCost() const = 0;
	virtual int GetUpgradeAmount() const = 0;
};


