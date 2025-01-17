#include "Framework.h"

ColorPrinter::ColorPrinter()
{
}

ColorPrinter::~ColorPrinter()
{
}

void ColorPrinter::SetTextColor(int colorNum)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorNum);

}

string ColorPrinter::ColoredText(const string& text, const string& colorCode)
{
    return colorCode + text + "\033[0m"; // \033[0m: 색상 초기화 코드
}

