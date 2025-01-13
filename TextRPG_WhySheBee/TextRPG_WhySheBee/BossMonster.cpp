#include "Framework.h"
#include "BossMonster.h"


void BossMonster::EnragedSkill()
{
	cout << GetName() << "이 잃은 체력의 절반을 회복합니다! " << endl;
	CurrentHP += (MaxHP - CurrentHP) / 2;
	cout << GetName() << " 체력: " << to_string(GetHealth());
}

void BossMonster::UseRandomSkill()
{
	int RandomSkill = rand() % 2;
	
	switch (RandomSkill)
	{
	case 0:
		FireBress();
		break;
	case 1:
		QuickAttack();
		break;
	default:
		FireBress();
		break;
	}
}

void BossMonster::FireBress()
{
	cout << GetName() << "이 용의 숨결 스킬로 공격합니다!" << endl;
	// PlaterChacter의 TakeDamaged 메서드 구현 필요.
	/*
	* 기본 공격력의 1.5배 공격
	*/
	cout << "Player 체력: " << to_string(Player->GetHealth()) << endl;
}

void BossMonster::QuickAttack()
{
	cout << GetName() << "이 재빠르게 두 번 공격합니다!" << endl;
	// PlaterChacter의 TakeDamaged 메서드 구현 필요.
	/*
	* 첫 번째는 기본 공격, 두 번째는 기본 공격의 0.5배 공격
	*/
	cout << "Player 체력: " << to_string(Player->GetHealth()) << endl;
}


