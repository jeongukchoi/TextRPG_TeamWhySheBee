#pragma once
class EquipmentDecorator : public Equipment
{
protected:
	Equipment* equipment;

public:
	EquipmentDecorator(Equipment* e) : equipment(e) {}
	virtual ~EquipmentDecorator() { delete equipment; }
};

