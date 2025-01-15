#include "Framework.h"

// 턴제 전투 메서드
bool BattleManager::Battle() 
{
	ColorPrinter printer;
	ConsoleManager Console;

	Console.ClearScreen();

	Player->IncreaseStat(HP, Player->GetMaxHealth());
	// 현재 플레이어의 레벨 저장
	PlayerLevel = Player->GetLevel();
	Player->DisplayStatus();

	// 플레이어 레벨에 기반해서 몬스터 생성
	CreateMonster();
	
	if (Player == nullptr || Monster == nullptr)
	{
		cout << "전투 준비 오류 발생";
		return false;
	}
	
	// 공격 딜레이 설정
	int MonsterAttackDelay = Monster->GetAttackDelay();
	int CurrentAttackDelay = PlayerAttackDelay;

	cout << "전투를 시작합니다!\n\n";
	
	// 스텟 출력
	Console.DrawVs();
	DisplayMonsterStats();

	// 전투 시작
	while (!IsPlayerDead() && !IsMonsterDead())
	{
		//턴 진행 
		MonsterAttackDelay--;
		CurrentAttackDelay--;
		

		// 플레이어 공격
		if(CurrentAttackDelay <= 0)
		{
			PlayerAttack();
			CurrentAttackDelay = PlayerAttackDelay;
			Sleep(2000);
		}

		// 플레이어 전투 승리
		if (IsMonsterDead())
		{
			cout << printer.ColoredText(Player->GetName(), RED) << "이(가) " << printer.ColoredText(Monster->GetName(), BLUE) << "를 처치했습니다!" << endl;
			
			std::cout << "전투 승리!" << std::endl;

			// 전투 보상 획득
			GetRewards();
			
			//30 퍼센트 확률로 아이템 드랍 후 플레이어에게 전달
			GetRandomItem();

			Monster.reset();
			Console.ClearScreen();
			// 승리 반환 레벨10 이상인 경우는 엔딩 조건 맞게 변경
			return PlayerLevel < 10;
		}

		// 몬스터 공격
		if (MonsterAttackDelay <= 0)
		{
			MonsterAttack();
			MonsterAttackDelay = Monster->GetAttackDelay();
			Sleep(4000);			

			Console.ClearScreen();;
		}


		// 플레이어 전투 패배
		if (IsPlayerDead())
		{
			cout << Player->GetName() << "이(가) 사망했습니다." << endl;
			std::cout << "전투 패배..." << std::endl;
			Monster.reset();
			Console.ClearScreen();
			// 패배 반환
			return false;
		}
	}
	throw runtime_error("== 비정상 전투 종료: BattleManager::Battle 메서드 오류 ==");
}

/*
*
*
*/

// 몬스터 생성 및 전투 시작 알림 메서드
void BattleManager::CreateMonster()
{
	// 일반 몬스터 랜덤 생성
	if (PlayerLevel < 10)
	{
		Monster = EnemyFactory::CreateBasicMonster(PlayerLevel);
		cout << "몬스터 " << Monster->GetName() << "등장합니다!";
		/*cout << " 체력: " << to_string(Monster->GetHealth()) << ", 공격력 : " << to_string(Monster->GetDamage()) << endl;*/
	}
	// 보스 몬스터 생성
	else
	{
		Monster = EnemyFactory::CreateBossMonster(PlayerLevel);
		cout << "두두두둥~ 쾅!" << endl;
		cout << "보스 몬스터 " << Monster->GetName() << "이 불을 내뿜으며 등장합니다!";
		/*cout << " 체력: " << to_string(Monster->GetHealth()) << ", 공격력 : " << to_string(Monster->GetDamage()) << endl;*/
	}
}

// 플레이어 공격 메서드
void BattleManager::PlayerAttack()
{
	RandomUseItem();
	ColorPrinter printer;

	cout << printer.ColoredText(Player->GetName(),RED) << "이(가) " << printer.ColoredText(Monster->GetName(), BLUE) << "를(을) 공격합니다! ";
	int HitDamage = static_cast<int>(Player->Attack() * AttackMinaMax(0.7f, 1.0f));
	Monster->TakeDamaged(HitDamage);

	DisplayMonsterStats();
	/*cout << Monster->GetName() << " 체력: " << to_string(Monster->GetHealth()) << endl ;*/
}

// 몬스터 공격 메서드
void BattleManager::MonsterAttack()
{
	BossMonster* Boss = dynamic_cast<BossMonster*>(Monster.get());

	ColorPrinter printer;
	// 보스 몬스터 공격 로직
	if (Boss != nullptr)
	{
		int RandomValue = rand() % 100;
		if (RandomValue < 30)
		{
			Boss->UseRandomSkill();
		}
		else
		{
			cout << Boss->GetName() << "이 "<< Player->GetName() << " 에게 일반 공격을 합니다! ";
			Player->TakeDamage(Monster->GetDamage());
			
			//cout << "Player 체력: " << to_string(Player->GetHealth()) << endl;
		}
	}
	// 일반 몬스터 공격 로직
	else
	{
		cout << printer.ColoredText(Monster->GetName(), BLUE) << "이(가)" << printer.ColoredText(Player->GetName(), RED) <<"를 공격합니다! ";
		Player->TakeDamage(Monster->GetDamage());
		//cout << "Player 체력: " << to_string(Player->GetHealth()) << endl;
	}
}

// 플레이어 사망 확인 메서드
bool BattleManager::IsPlayerDead()
{
	if (Player->GetHealth() <= 0)
	{
		return true;
	}
	return false;
}

// 몬스터 사망 확인 메서드
bool BattleManager::IsMonsterDead()
{
	return Monster->IsDead;
}

// 전투 승리 보상 메서드
void BattleManager::GetRewards()
{
	ColorPrinter printer;
	if (PlayerLevel < 10)
	{
		int M_Exp = MonsterExp[PlayerLevel - 1];
		int M_Gold = rand() % 101 + 100;

		Player->IncreaseStat(EXP, M_Exp);
		Player->IncreaseStat(GOLD, M_Gold);

		cout << printer.ColoredText(Player->GetName(), RED) << "이(가) " << printer.ColoredText(to_string(M_Exp), YELLOW)
			<< " EXP와" << printer.ColoredText(to_string(M_Gold), YELLOW) << " Gold를 획득했습니다." << endl;
		cout << "현재 EXP: " << printer.ColoredText(to_string(Player->GetExperience()), YELLOW) << ", Gold: " << printer.ColoredText(to_string(Player->GetGold()), YELLOW) << endl;
	}
}

// 확률적으로 아이템 드롭 및 인벤토리 저장 메서드
void BattleManager::GetRandomItem()
{
	int RandomNumber = rand() % 100;
	if (RandomNumber < 30)
	{
		ItemID DropItem = Item_Manager.GetRandomItem();
		PlayerInventory->AddItem(DropItem);
	}
}

// 확률적으로 아이템 사용 메서드
void BattleManager::RandomUseItem()
{
	int RandomNumber = rand() % 100;
	if (RandomNumber < 30)
	{
		PlayerInventory->UseConsumables();
	}
}

float BattleManager::AttackMinaMax(float min , float max)
{
	random_device Rd; // 시드용 랜덤 장치
	mt19937 Gen(Rd()); //  Mersenne Twister dpswls
	uniform_real_distribution<float> Dis(0.7f, 1.0); //0.7부터 1.0까지 균일 하게
	float randomValue = Dis(Gen);
	return randomValue;
}

void BattleManager::DisplayMonsterStats()
{
	Console.SetSettingPosition(2,0,0);
	Console.DrawRectangle(60, 20, 20, 8);

	Console.SetSettingPosition(2, 1, 1);
	cout << "     [" + Monster->GetName() + "]  ";

	Console.SetSettingPosition(2, 3, 1);
	cout << "  체력:    " << resetiosflags(ios::showbase | ios::internal | ios::showpos) << setfill(' ') << setw(0) << to_string(Monster->GetHealth());

	Console.SetSettingPosition(2, 5, 1);
	cout << "  공격력:  " << resetiosflags(ios::showbase | ios::internal | ios::showpos) << setfill(' ') << setw(0) << to_string(Monster->GetDamage());

	Console.SetCursorPosition(0, 0);
}

