#pragma once

class HealthPotion : public Item {
private:
	string ItemName;
	STATUS TargetStat;
	const int StatAmount = 50;

public:
	HealthPotion();
	string GetName() const override { return ItemName; }
	STATUS GetTargetStat() const override { return TargetStat; }
	int GetStatAmount() const override { return StatAmount; }

	void Use(PlayerCharacter* character) override;
	void PrintItemInfo();
};

