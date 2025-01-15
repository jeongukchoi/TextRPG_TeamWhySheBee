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

	//전투 턴
	int Battle_Turn = 1;	
	// 공격 딜레이 설정
	int MonsterAttackDelay = Monster->GetAttackDelay();
	int CurrentAttackDelay = PlayerAttackDelay;

	cout << "전투를 시작합니다!\n\n";
	
	Sleep(1000);
	Console.ClearScreen();

	// 스텟 출력
	Console.DrawVs();
	DisplayMonsterStats();

	// 전투 시작
	while (!IsPlayerDead() && !IsMonsterDead())
	{		
		PrintBattle();

		//현재 턴 
		Texts.push_back(printer.ColoredText("현재 턴 : ", WHITE) + printer.ColoredText(to_string(Battle_Turn++), GREEN));

		//턴 진행 
		MonsterAttackDelay--;
		CurrentAttackDelay--;

		// 플레이어 공격
		if(CurrentAttackDelay <= 0)
		{		
			PlayerAttack();
			CurrentAttackDelay = PlayerAttackDelay;
		}

		// 플레이어 전투 승리
		if (IsMonsterDead())
		{
			Texts.push_back(printer.ColoredText(Player->GetName(), RED) + "이(가) " + printer.ColoredText(Monster->GetName(), BLUE) + "를 처치했습니다!");		
			Texts.push_back("전투 승리!");

			GetRewards();
			PrintBattle();

			// 전투 보상 획득
			Console.ClearScreen();
			//30 퍼센트 확률로 아이템 드랍 후 플레이어에게 전달
			GetRandomItem();

			Monster.reset();

			Battle_Turn = 1;
			CurrentTextYposition = 0;
			
			// 승리 반환 레벨10 이상인 경우는 엔딩 조건 맞게 변경
			return PlayerLevel < 10;
		}

		// 몬스터 공격
		if (MonsterAttackDelay <= 0)
		{
			MonsterAttack();
			MonsterAttackDelay = Monster->GetAttackDelay();		

		}


		// 플레이어 전투 패배
		if (IsPlayerDead())
		{
			Texts.push_back(Player->GetName() + "이(가) 사망했습니다." );
			Texts.push_back("전투 패배...");
			PrintBattle();
			Monster.reset();
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
		Texts.push_back("몬스터 " + Monster->GetName() + "등장!");		
	}
	// 보스 몬스터 생성
	else
	{
		Monster = EnemyFactory::CreateBossMonster(PlayerLevel);
		Texts.push_back("두두두둥~ 쾅!" );
		Texts.push_back("보스 몬스터 " + Monster->GetName() + "이 불을 내뿜으며 등장합니다!");		
	}
}

// 플레이어 공격 메서드
void BattleManager::PlayerAttack()
{
	RandomUseItem();
	ColorPrinter printer;
	Texts.push_back(printer.ColoredText(Player->GetName(), RED) + "이(가) 공격!! ");
	
	int HitDamage = static_cast<int>(Player->Attack() * AttackMinaMax(0.7f, 1.0f));

	string NextText = Player->GetSkillName();		
	//함수화를 해야할지 생각중 람다도 가능
	if(NextText != "")
	{
		Texts.push_back(NextText);
	}
	
	NextText = Monster->TakeDamaged(HitDamage);

	if (NextText != "")
	{
		Texts.push_back(NextText);
	}

	Texts.push_back("[" + Monster->GetName() + "]의 체력이 [" + to_string(HitDamage) + "] 감소했습니다.");
	DisplayMonsterStats();	
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
			Texts.push_back(Boss->GetName() + "이 일반 공격을 합니다! ");
			Player->TakeDamage(Monster->GetDamage());
			Texts.push_back("[" + Player->GetName() + "]의 체력이 [" + to_string(Monster->GetDamage()) + "] 감소했습니다.");
		}
	}
	// 일반 몬스터 공격 로직
	else
	{
		Texts.push_back(printer.ColoredText(Monster->GetName(), BLUE) + "이(가) 공격!! ");
		Player->TakeDamage(Monster->GetDamage());
		Texts.push_back("[" + Player->GetName() + "]의 체력이 [" + to_string(Monster->GetDamage()) + "] 감소했습니다.");
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

		Texts.push_back(printer.ColoredText(Player->GetName(), RED) + "이(가) " + printer.ColoredText(to_string(M_Exp), YELLOW)
			+ " EXP와" + printer.ColoredText(to_string(M_Gold), YELLOW) + " Gold 획득 !" );
	}
}

// 확률적으로 아이템 드롭 및 인벤토리 저장 메서드
void BattleManager::GetRandomItem()
{
	int RandomNumber = rand() % 100;
	if (RandomNumber < 100)
	{
		ItemID DropItem = Item_Manager.GetRandomItem();
		PlayerInventory->AddItem(DropItem);
		Sleep(1000);
	}
}

// 확률적으로 아이템 사용 메서드
void BattleManager::RandomUseItem()
{
	int RandomNumber = rand() % 100;
	if (RandomNumber < 100)
	{
		string text = PlayerInventory->UseConsumables();
		if (text != "")
		{
			Texts.push_back(text);
		}
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


void BattleManager::PrintBattle()
{
	Console.ClearScreen();

	int TextIndex = CurrentTextYposition;
	int TextSize = Texts.size() - TextIndex;
	//현재 텍스트인덱스와 마지막 텍스트현재 있는 마지막 인덱스 0 -> 
	for (int i = 0; i < TextSize; i++)
	{
		Console.SetCursorPosition(10, i);
		cout << Texts[TextIndex++] << endl;
	}
	Sleep(200);

	//마지막 인덱스 설정
	CurrentTextYposition = Texts.size();
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

void BattleManager::CheckAndGetString(string txt)
{
		if (txt != "")
		{
			Texts.push_back(txt);
		}
		
}



