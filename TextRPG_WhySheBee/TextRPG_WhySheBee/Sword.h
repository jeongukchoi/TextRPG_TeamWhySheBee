#pragma once
class Sword : public Equipment
{
private:
	string ItemName;
	ItemType Type;
	int Price;
	STATUS TargetStat;
	int StatAmount;

public:
	Sword();
	// 아이템 이름
	string GetName() const override { return ItemName; }
	// 아이템 종류
	ItemType GetType() const override { return Type; }
	// 아이템 가격
	int GetPrice() const override { return Price; }
	// 변경할 스탯
	STATUS GetTargetStat() const override { return TargetStat; }
	// 변경할 스탯 수치
	int GetStatAmount() const override { return StatAmount; }

	// 아이템 정보 출력
	void PrintItemInfo() override;
	// 아이템 사용(장비 착용)
	void Use() override;
	

	int GetEquipmentLevel() const override { return 0; }
};

