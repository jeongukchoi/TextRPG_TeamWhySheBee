#include "Framework.h"
#include "GameManager.h"

using namespace std;

GameManager::GameManager() : bossCleared(false) {}

void GameManager::StartGame()
{
    cout << "게임을 시작합니다. " << endl;
    CreateCharacter();
    while (true)
    {
        Battle();
        if (bossCleared)
        {
            ShowEnding();
            break;
        }

        /*
        cout << "상점을 방문하시겠습니까? (Y/N): ";
        char choice;
        cin >> choice;

        if (choice == 'Y' || choice == 'y')
        {
            VisitShop();
        }
        else if (choice == 'N' || choice == 'n')
        {
            Battle();
        }

        */
        if (PlayerCharacter::GetInstance()->GetLevel() >= 10)
        {
            cout << "레벨 10에 도달했습니다! 보스와의 전투를 시작합니다." << endl;
            break;
        }
    }
}

void GameManager::CreateCharacter()
{
    string playerName;

    cout << "플레이어 캐릭터의 이름을 입력하세요: ";
    getline(cin, playerName); // 캐릭터 이름 입력 받기

    PlayerCharacter* player = PlayerCharacter::GetInstance(playerName);

}

void GameManager::DisplayInventory()
{
    cout << "인벤토리 목록" << endl;
    // 인벤토리 출력 로직
}

void GameManager::VisitShop()
{
    cout << "상점에 방문하셨습니다!" << endl;
    // 상점 방문 로직 (아이템 구매 등)
}

void GameManager::ShowEnding()
{
    cout << "축하합니다! 게임 엔딩을 보셨습니다!" << endl;
    cout << "엔딩 크레딧:" << endl;
    // 엔딩 크레딧 출력
    cout << "게임을 플레이 해주셔서 감사합니다!" << endl;
}

void GameManager::Battle() {
    // BattleManager 객체 생성
    BattleManager battleManager;

    // 전투 실행
    bool battleResult = battleManager.Battle();

    // 결과 처리
    if (battleResult) {
        std::cout << "전투 승리!" << std::endl;
    }
    else {
        std::cout << "전투 패배..." << std::endl;
        // 패배 시 추가 처리 로직
    }
}