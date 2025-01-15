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

void ConsoleManager::SetSettingPosition(int num,int y,int x)
{
    switch (num)
    {
        case 0: 
        {
            CursorPosition position = cursorPositions["PlayerStatus"];
            SetCursorPosition(position.first+x, position.second+y);
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


