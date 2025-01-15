#pragma once
class UniquePotion : public Item
{
private:
	string ItemName;
	ItemType Type;
	int Price;
	STATUS TargetStat;
	int StatAmount;

public:
	UniquePotion();
	~UniquePotion() {}
	string GetName() const override { return ItemName; }
	ItemType GetType() const override { return Type; }
	int GetPrice() const override { return Price; }
	ItemID GetID() const override { return UNIQUE_POTION; }
	STATUS GetTargetStat() const override { return TargetStat; }
	// 변경할 스탯 스트링
	string GetTargetStatString() const override;
	int GetStatAmount() const override { return StatAmount; }

	void Use() override;
	string GetItemInfoString();
	void PrintItemInfo();
};

