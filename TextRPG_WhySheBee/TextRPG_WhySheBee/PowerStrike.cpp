#include "Framework.h"

PowerStrike::~PowerStrike()
{
}

int PowerStrike::Activate(int attackPower, int stat)
{
	std::unique_ptr<ColorPrinter> printer = std::make_unique<ColorPrinter>();
	cout << printer->ColoredText("파워 스트라이크!!!", GREEN) << endl;
	return 0;
}
