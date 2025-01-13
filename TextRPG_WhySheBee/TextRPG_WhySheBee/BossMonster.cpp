#include "Framework.h"


void BossMonster::EnragedSkill()
{
	cout << Name << "이 잃은 체력의 절반을 회복합니다! " << endl;
	CurrentHP += (MaxHP - CurrentHP) / 2;
	cout << Name << " 체력: " << CurrentHP;
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
		QuickAttack();
		break;
	}
}

void BossMonster::FireBress()
{
	cout << Name << "이 용의 숨결 스킬로 공격합니다!" << endl;
	
	// 기본 공격력의 1.5배 데미지
	Player->TakeDamage(Damage * 1.5);
}

void BossMonster::QuickAttack()
{
	cout << Name << "이 재빠르게 두 번 공격합니다!" << endl;

	// 기본 공격력, 기본 공격력 0.3배 데미지
	Player->TakeDamage(Damage);
	Player->TakeDamage(Damage * 0.3);
}



