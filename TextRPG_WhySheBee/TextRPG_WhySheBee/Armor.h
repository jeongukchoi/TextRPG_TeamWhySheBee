#pragma once
class Armor : public Equipment
{
private:
	string ItemName;
	ItemType Type;
	int Price;
	STATUS TargetStat;
	int StatAmount;

public:
	Armor();
	// 아이템 이름
	string GetName() const override { return ItemName; }
	// 아이템 종류
	ItemType GetType() const override { return Type; }
	// 아이템 가격
	int GetPrice() const override { return Price; }
	// 아이템 ID
	ItemID GetID() const override { return ARMOR; }

	// 변경할 스탯
	STATUS GetTargetStat() const override { return TargetStat; }
	// 변경할 스탯 스트링
	string GetTargetStatString() const override { return "최대 체력"; }
	// 변경할 스탯 수치
	int GetStatAmount() const override { return StatAmount; }

	// 강화 비용
	int GetUpgradeCost() const override { return 0; }
	// 초기 강화 수치 = 0
	int GetUpgradeAmount() const override { return 0; }

	// 아이템 정보 출력
	void PrintItemInfo() override;
	// 아이템 사용(장비 착용)
	void Use() override;


	int GetEquipmentLevel() const override { return 0; }
};


