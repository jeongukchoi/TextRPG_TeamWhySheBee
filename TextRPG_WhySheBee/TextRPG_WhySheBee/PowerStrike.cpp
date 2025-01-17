#include "Framework.h"

PowerStrike::~PowerStrike()
{
}

int PowerStrike::Activate(int attackPower, int stat)
{
	/*std::unique_ptr<ColorPrinter> printer = std::make_unique<ColorPrinter>();
	cout << printer->ColoredText("파워 스트라이크!!!", GREEN) << endl;*/
	std::unique_ptr<ColorPrinter> printer = std::make_unique<ColorPrinter>();
	_skillName = printer->ColoredText("파워 스트라이크!!!", GREEN);
	int damage=0;
	damage = attackPower + (stat * 5);
	return damage;
}
