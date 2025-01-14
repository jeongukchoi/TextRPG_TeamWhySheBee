#include "Framework.h"

int MagicArrow::Activate(int attackPower, int stat)
{
	std::unique_ptr<ColorPrinter> printer = std::make_unique<ColorPrinter>();
	cout << printer->ColoredText("매직 미사일!!!", GREEN) << endl;
    return 0;
}
