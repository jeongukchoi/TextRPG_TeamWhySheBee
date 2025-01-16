#include "Framework.h"

using namespace std;

GameManager::GameManager() : over(false) {}

void GameManager::StartGame()
{

    ConsoleManager* console = new ConsoleManager();
    console->ClearConsoleSizeScreen();

    CreateCharacter();

    Shop* shop = new Shop();

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

        cout << "상점을 방문하시겠습니까? (Y 입력...): ";
        string choice;
        cin >> choice;

        
        if (choice == "NBC" || choice == "nbc")
        {
            PlayerCharacter* player = PlayerCharacter::GetInstance().get();

            for (int i = player->GetLevel(); i < 10; ++i)
            {
                int experienceToNextLevel = i * 10 - player->GetExperience(); // 다음 레벨까지 필요한 경험치
                player->IncreaseStat(EXP, experienceToNextLevel); // 필요한 경험치를 추가
            }

            player->IncreaseStat(MAXHP, 999 - player->GetMaxHealth()); // 최대 체력을 999로 설정
            player->IncreaseStat(HP, 999 - player->GetHealth()); // 현재 체력을 999로 설정
            player->IncreaseStat(ATTACK, 999 - player->GetAttack()); // 공격력을 999로 설정

            
            cout << "==========================================" << endl;
            cout << "Enable CHEAT" << endl;
            cout << "==========================================" << endl;
        }
        

        if (choice[0] == 'Y' || choice[0] == 'y')
        {
            VisitShop(shop);
        }

        else
        {
            continue;
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
    bool _isfirst = true;

    cout << "플레이어 캐릭터의 이름을 입력하세요: ";
    do
    {
        getline(cin, playerName);

        if (playerName.empty() || playerName.find_first_not_of(' ') == string::npos)
        {
            if (!_isfirst)
            {
                cout << "이름을 다시 작성해주세요." << endl;
            }
        }
        _isfirst = false;
    } while (playerName.empty() || playerName.find_first_not_of(' ') == string::npos);

   /* while (true)
    {
        cout << "플레이어 캐릭터의 이름을 입력하세요: ";
        cin >> playerName;

        if (!playerName.empty() && playerName.find_first_not_of(' ') != string::npos)
        {
            break; 
        }
        else
        {
            cout << "이름을 다시 작성해주세요." << endl;
        }
    }*/

    _isfirst = true;
    cout << "직업을 선택하세요: " << endl;
   
    while (true)
    {
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
            {
                cout << "선택하신직업이 없습니다. 다시 선택해주세요 " << endl;
            }
            continue;
        }
        return ; 
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