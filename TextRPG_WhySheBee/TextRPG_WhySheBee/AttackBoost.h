#pragma once

class AttackBoost : public Item {
private:
	string ItemName;
	ItemType Type;
	int Price;
	STATUS TargetStat;
	int StatAmount;

public:
	AttackBoost();
	string GetName() const override { return ItemName; }
	ItemType GetType() const override { return Type; }
	int GetPrice() const override { return Price; }
	STATUS GetTargetStat() const override { return TargetStat; }
	int GetStatAmount() const override { return StatAmount; }

	void Use() override;
	void PrintItemInfo();
};



