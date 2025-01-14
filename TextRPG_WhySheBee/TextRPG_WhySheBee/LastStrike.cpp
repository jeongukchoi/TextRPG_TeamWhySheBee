#include "Framework.h"

int LastStrike::Activate(int attackPower, int stat)
{
	int damage = 0;

	std::unique_ptr<ColorPrinter> printer = std::make_unique<ColorPrinter>();
	cout << printer->ColoredText("최후의 일격!!!!", CYAN) << endl;

	damage = attackPower + (stat * 30);
    return damage;
}
