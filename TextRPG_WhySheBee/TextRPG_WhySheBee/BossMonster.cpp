#include "Framework.h"


string BossMonster::EnragedSkill()
{
	CurrentHP += (MaxHP - CurrentHP) / 2;
	return Name + "이 잃은 체력의 절반을 회복합니다!";
}

string BossMonster::UseRandomSkill()
{
	int RandomSkill = rand() % 2;
	
	switch (RandomSkill)
	{
	case 0:
		FireBress();
		return Name + "이 용의 숨결 스킬로 공격합니다!";
	case 1:
		QuickAttack();
		return Name + "이 재빠르게 두 번 공격합니다!";
	default:
		QuickAttack();
		return Name + "이 재빠르게 두 번 공격합니다!";
	}
}

void BossMonster::FireBress()
{
	// 기본 공격력의 1.5배 데미지
	Player->TakeDamage(Damage * 1.5);
}

void BossMonster::QuickAttack()
{
	// 기본 공격력, 기본 공격력 0.3배 데미지
	Player->TakeDamage(Damage);
	Player->TakeDamage(Damage * 0.3);
}



