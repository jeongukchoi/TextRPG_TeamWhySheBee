#include "Framework.h"

int LastStrike::Activate(int attackPower, int stat)
{
	int damage = 0;

	std::unique_ptr<ColorPrinter> printer = std::make_unique<ColorPrinter>();
	_skillName = printer->ColoredText("최후의 일격!!!!", CYAN);
	damage = attackPower + (stat * 10);
    return damage;
}
