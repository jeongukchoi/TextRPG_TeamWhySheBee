#include "Framework.h"

int Meteor::Activate(int attackPower, int stat)
{
	std::unique_ptr<ColorPrinter> printer = std::make_unique<ColorPrinter>();
	cout << printer->ColoredText("메테오!!!!!", RED) << endl;
    return 0;
}
