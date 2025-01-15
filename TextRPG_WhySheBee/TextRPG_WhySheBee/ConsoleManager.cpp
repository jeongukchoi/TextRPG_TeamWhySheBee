#include "Framework.h"
#include "ConsoleManager.h"

ConsoleManager::ConsoleManager()
{
    Console = GetStdHandle(STD_OUTPUT_HANDLE);

    // 콘솔 버퍼 크기 설정
    COORD BufferSize = { static_cast<SHORT>(120), static_cast<SHORT>(50) };
    SetConsoleScreenBufferSize(Console, BufferSize);

    SMALL_RECT WindowSize = { 0, 0, static_cast<SHORT>(119), static_cast<SHORT>(49) };
    SetConsoleWindowInfo(Console, TRUE, &WindowSize);

    // 전투 로직에서 스텟창 위치 설정
    cursorPositions["PlayerStatus"] = { 2, 20 };
    cursorPositions["VS"] = { 35, 20 };
    cursorPositions["MonsterStatus"] = { 60, 20 };
}

void ConsoleManager::ClearScreen()
{
    SetCursorPosition(0, 0);

    DWORD count;

    // 현재 콘솔 버퍼 정보 저장
    CONSOLE_SCREEN_BUFFER_INFO ConsoleBuffer;
    GetConsoleScreenBufferInfo(Console, &ConsoleBuffer);

    // 콘솔의 출력 영역만큼 공백으로 채움
    FillConsoleOutputCharacter(Console, ' ', 60 * 16, coord, &count);
    // 커서 초기 위치 0,0 이동
    SetCursorPosition(0, 0);
    SetConsoleCursorPosition(Console, coord);

    Sleep(500);
}

void ConsoleManager::ClearConsoleSizeScreen()
{
    SetCursorPosition(0, 0);

    DWORD count;

    // 현재 콘솔 버퍼 정보 저장
    CONSOLE_SCREEN_BUFFER_INFO ConsoleBuffer;
    GetConsoleScreenBufferInfo(Console, &ConsoleBuffer);

    // 콘솔의 출력 영역만큼 공백으로 채움
    FillConsoleOutputCharacter(Console, ' ', ConsoleBuffer.dwSize.X * ConsoleBuffer.dwSize.Y, coord, &count);
    // 커서 초기 위치 0,0 이동
    SetCursorPosition(0, 0);
    SetConsoleCursorPosition(Console, coord);

    Sleep(500);
}

void ConsoleManager::DisplayMainMenu()
{
    COORD coord = { 5,5 };

    SetConsoleCursorPosition(Console, coord);

    const char* Title[] =
    {
        "888888ba                                                  .d88888b  dP                                     ",
        "88    `8b                                                 88.    '  88                                      ",
        "88     88 88d888b..d8888b.  .d8888b..d8888b. 88d888b.    `Y88888b.  88.d8888b.  dP    dP. d8888b. 88d888b. ",
        "88     88 88'  `88 88'  `88 88'  `88 88'  `88 88'  `88          `8b 88 88'  `88 88    88 88ooood8 88'  `88 ",
        "88    .8P 88       88.  .88 88.  .88 88.  .88 88    88    d8'   .8P 88 88.  .88 88.  .88 88.  ... 88       ",
        "8888888P  dP       `88888P8 `8888P88 `88888P' dP    dP     Y88888P  dP `88888P8 `8888P88 `88888P' dP       ",
        "ooooooooooooooooooooooooooooo~~~~.88~oooooooooooooooooooooooooooooooooooooooooooo~~~~.88~oooooooooooooooooo",
        "                             d8888P                                              d8888P                   "
    };

	for (int i = 0; i < 8; i++)
	{
		SetConsoleCursorPosition(Console, coord);
        int Idx = i;
		
		cout << Printer.ColoredText(Title[i], to_string(Idx + 1)) << endl;
        coord.Y++;
	}

    cout << endl << endl;

    SetCursorPosition(50, 20);
    cout << "> 게임 시작 : 1";
    SetCursorPosition(50, 22);
    cout << "> 게임 종료 : 2";
	SetCursorPosition(50, 24);
}

void ConsoleManager::SetCursorPosition(int x, int y)
{
    COORD position = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

void ConsoleManager::DrawRectangle(int x, int y, int width, int height)
{
    // 상단
    SetCursorPosition(x, y);
    cout << string(width, '-');

    // 좌측 및 우측
    for (int i = y + 1; i < y + height - 1; ++i) {
        SetCursorPosition(x, i);
        cout << "|";
        SetCursorPosition(x + width - 1, i);
        cout << "|";
    }

    // 하단
    SetCursorPosition(x, y + height - 1);
    cout << string(width, '-');
}

void ConsoleManager::DrawVs()
{

    SetSettingPosition(1, 0);
    cout << "#   #   ### ";
    SetSettingPosition(1, 1);
    cout << "#   #  #    ";
    SetSettingPosition(1, 2);
    cout << "#  #   #    ";
    SetSettingPosition(1, 3);
    cout << "#  #    #   ";
    SetSettingPosition(1, 4);
    cout << "# #      #  ";
    SetSettingPosition(1, 5);
    cout << "#     ###   ";


}

void ConsoleManager::SetSettingPosition(int num, int y, int x)
{
    switch (num)
    {
    case 0:
    {
        CursorPosition position = cursorPositions["PlayerStatus"];
        SetCursorPosition(position.first + x, position.second + y);
    }
    break;
    case 1:
    {
        CursorPosition position = cursorPositions["VS"];
        SetCursorPosition(position.first + x, position.second + y);
    }
    break;
    case 2:
    {
        CursorPosition position = cursorPositions["MonsterStatus"];
        SetCursorPosition(position.first + x, position.second + y);
    }
    break;
    default:
        return;

    }
}

void ConsoleManager::DisplayDialogue(const string& dialogue, int startX, int startY, int width, int height, int offsetX, int offsetY)
{
    // 커서 위치에 오프셋 반영
    int CurrX = startX + 1 + offsetX; // 변하지 않음
    int CurrY = startY + 1 + offsetY;
    /*** 커서를 옮겨가며 "\n"으로 구분된 스트링을 한 줄씩 출력 ***/
    size_t CurrPos = 0;
    size_t NextPos = 0;
    string Delimiter = "\n"; // parse 기준이 되는 스트링
    // NextPos : CurrPos 이후 처음으로 등장하는 Delimiter 의 위치
    while ((NextPos = dialogue.find(Delimiter, CurrPos)) != string::npos)
    {
        // 커서 위치 조정 후, CurrPos 부터 NextPos 까지의 string 출력
        SetCursorPosition(CurrX, CurrY++);
        cout << dialogue.substr(CurrPos, NextPos - CurrPos);
        // CurrPos 위치를 Delimiter 이후로 업데이트
        CurrPos = NextPos + Delimiter.length();
    }
    // 마지막으로 찾은 Delimiter 이후의 스트링 출력
    SetCursorPosition(CurrX, CurrY++);
    cout << dialogue.substr(CurrPos);
    // 대화 창의 테두리 그리기
    DrawRectangle(startX, startY, width, height + 2 * offsetY);
    SetCursorPosition(0, 0);
}
