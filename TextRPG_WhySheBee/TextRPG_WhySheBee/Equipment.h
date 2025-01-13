#pragma once
class Equipment : public Item
{
public:
	virtual ~Equipment() {}
	// 장비 강화 레벨
	virtual int GetEquipmentLevel() const = 0;
};

