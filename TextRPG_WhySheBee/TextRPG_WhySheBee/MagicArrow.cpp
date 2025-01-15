#include "Framework.h"

int MagicArrow::Activate(int attackPower, int stat)
{
	/*std::unique_ptr<ColorPrinter> printer = std::make_unique<ColorPrinter>();
	cout << printer->ColoredText("매직 미사일!!!", GREEN) << endl;*/

	_skillName = "매직 미사일!!!";

	int damage = 0;

	damage = attackPower + (stat * 70);
	return damage;
}

