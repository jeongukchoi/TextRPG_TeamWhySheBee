#pragma once

class ColorPrinter
{

public:
	ColorPrinter();
	~ColorPrinter();

	void SetTextColor(int colorNum);
	string ColoredText(const string& text, const string& colorCode);

};