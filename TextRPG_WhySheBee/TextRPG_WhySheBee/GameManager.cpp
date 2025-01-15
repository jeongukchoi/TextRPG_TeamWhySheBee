#include "Framework.h"
#include "GameManager.h"

using namespace std;

GameManager::GameManager() : over(false) {}

void GameManager::StartGame()
{
    cout << "게임을 시작합니다. " << endl;
    CreateCharacter();
    Shop* shop = new Shop();
    ConsoleManager* console = new ConsoleManager();
    while (true)
    {


        Battle();
        if (over)
        {
            console->ClearScreen();
            ShowEnding();
            return;
        }


       console->ClearScreen();
        
        cout << "상점을 방문하시겠습니까? (Y/N): ";
        char choice;
        cin >> choice;

        if (choice == 'Y' || choice == 'y')
        {
            VisitShop(shop);
        }       

        


        if (PlayerCharacter::GetInstance()->GetLevel() >= 10)
        {
            cout << "레벨 10에 도달했습니다! 보스와의 전투를 시작합니다." << endl;
            //break;
        }
    }
}

void GameManager::CreateCharacter()
{
    string playerName;
    int playerJobNum;

    cout << "플레이어 캐릭터의 이름을 입력하세요: ";
    getline(cin, playerName); // 캐릭터 이름 입력 받기

    cout << "직업을 선택하세요: " << endl;
    cout << "1.전사 2.마법사 " << endl;
    cin >> playerJobNum;

    switch (playerJobNum)
    {
    case 1:
    {
        unique_ptr<PlayerCharacter>& player = PlayerCharacter::GetInstance(playerName, WARRIOR);
    }
    break;
    case 2:
    {
        unique_ptr<PlayerCharacter>& player = PlayerCharacter::GetInstance(playerName, MAGE);
    }
    break;
    default:
        cout << "선택하신직업이 없습니다. 다시 선택해주세요 " << endl;
    }
}

void GameManager::DisplayInventory()
{
    cout << "인벤토리 목록" << endl;
    // 인벤토리 출력 로직
    Inventory* inven = Inventory::GetInstance();
    inven->ShowInven();
}

void GameManager::VisitShop(Shop* shop)
{
    system("cls");
    cout << "상점에 방문하셨습니다!" << endl;

    shop->StartShop();
}

void GameManager::ShowEnding()
{
    cout << "\n";
    cout << "==========================================" << endl;
    cout << "                GAME CREDITS              " << endl;
    cout << "==========================================" << endl;
    cout << "\n";
    cout << "                제작: 1기 12조            " << endl;
    cout << "   강창훈, 김동현, 최정욱, 한상혁, 백인범, 김지황" << endl;
    cout << "\n";
    cout << "==========================================" << endl;
    cout << "        Thank you for playing our game!   " << endl;
    cout << "==========================================" << endl;
    cout << "\n";
    over = true;
}


void GameManager::Battle() 
{
    BattleManager battleManager;

    bool battleResult = battleManager.Battle();

    // 결과 처리
   
    if (!battleResult) 
    {
        over = true;
    }
  
}