#pragma once

using CursorPosition = pair<int, int>;

class ConsoleManager
{
public:
	ConsoleManager();

	// 콘솔 화면 클리어
	void ClearScreen();

	// 메인 메뉴 출력
	void DisplayMainMenu();

	// 커서 좌표 이동
	void SetCursorPosition(int x, int y);

	// 사각형 그리기
	void DrawRectangle(int x, int y, int width, int height);

	// VS 표시
	void DrawVs();

	// Stats 창 위치 설정
	void SetSettingPosition(int num, int y, int x = 0);

	// 위치, 크기, 오프셋 반영하여 스트링 출력 (네모칸 포함)
	void DisplayDialogue(const string& dialogue, int startX, int startY, int width, int height, int offsetX, int offsetY);

private:
	HANDLE Console;
	COORD coord;
	DWORD count;
	ColorPrinter Printer;
	unordered_map<string, CursorPosition> cursorPositions;
};
