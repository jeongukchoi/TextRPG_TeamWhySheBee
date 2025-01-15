#include "Framework.h"

int main()
{
    srand(static_cast<unsigned int>(time(NULL))); // 랜덤 시드 초기화

    // 메인 메뉴 출력;
	ConsoleManager Console;
	Console.DisplayMainMenu();

    GameManager gameManager; // GameManager 객체 생성
    gameManager.StartGame(); // 게임 시작 - 현재 무한 루프
    return 0; // 프로그램 종료
}


