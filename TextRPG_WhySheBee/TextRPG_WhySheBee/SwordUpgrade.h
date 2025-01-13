#pragma once
class SwordUpgrade : public EquipmentDecorator
{
protected:
	string UpgradeName;
	STATUS TargetStat;
	int UpgradeAmount;
	int UpgradeCost;

public:
	SwordUpgrade(Equipment* e);

	// 아이템 이름
	string GetName() const override { return equipment->GetName(); }
	// 아이템 종류
	ItemType GetType() const override { return equipment->GetType(); }
	// 아이템 가격
	int GetPrice() const override { return equipment->GetPrice() + UpgradeCost; }
	// 아이템 ID
	ItemID GetID() const override { return SWORD; }
	// 변경할 스탯
	STATUS GetTargetStat() const override { return TargetStat; }
	// 최종 스탯 수치
	int GetStatAmount() const override { return equipment->GetStatAmount() + UpgradeAmount; }
	// 업그레이드 수치
	int GetUpgradeAmount() const { return UpgradeAmount; }

	// 아이템 정보 출력
	void PrintItemInfo() override;
	// 아이템 사용(장비 착용)
	void Use() override;

	int GetEquipmentLevel() const override { return equipment->GetEquipmentLevel() + 1; }
};


