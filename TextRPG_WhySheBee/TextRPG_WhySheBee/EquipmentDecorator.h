#pragma once
class EquipmentDecorator : public Equipment
{
protected:
	Equipment* equipment;

public:
	EquipmentDecorator(Equipment* e) : equipment(e) {}
	virtual ~EquipmentDecorator() { delete equipment; }
	virtual int GetUpgradeCost() const = 0;
	// 변경할 스탯 스트링
	string GetTargetStatString() const override { return equipment->GetTargetStatString(); }
};


