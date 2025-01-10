#pragma once

class AttackBoost : public Item {
private:
	string ItemName;
	STATUS TargetStat;
	const int StatAmount = 10;

public:
	AttackBoost();
	string GetName() const override { return ItemName; }
	//STATUS GetTargetStat() const override { return TargetStat; }
	int GetStatAmount() const override { return StatAmount; }

	void Use(PlayerCharacter* character) override;
	void PrintItemInfo();
};


