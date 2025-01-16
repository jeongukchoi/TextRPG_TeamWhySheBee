#include "Framework.h"

int main()
{
    srand(static_cast<unsigned int>(time(NULL))); // 랜덤 시드 초기화

    // 메인 메뉴 출력;
	ConsoleManager Console;
    GameManager gameManager; // GameManager 객체 생성

	Console.DisplayMainMenu();
    Console.DrawRectangle(0, 0, 120, 30);
    Console.SetCursorPosition(50, 26);

    int num;
    cin >> num;

    if (num == 1)
    {
        cout << "게임을 시작합니다. " << endl;
        gameManager.StartGame(); // 게임 시작 - 현재 무한 루프
    }
    else
    {
        return 0;
    }
    
    delete Inventory::GetInstance();

    return 0; // 프로그램 종료
}


