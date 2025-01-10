#include "Framework.h"
#include "BaseMonster.h"

BaseMonster::BaseMonster(const string& name, const int& PlayerLevel)
{
	Calculate_HPandDamage(PlayerLevel);

	Name = name;
	CurrentHP = MaxHP;
	IsDead = false;

	CurrentState = new NormalState(); //상태 객체 동적 생성
}

BaseMonster::~BaseMonster()
{
	delete CurrentState; // 상태 객체 동적 해제
}

// MaxHP와 Damage 초기화 메서드
void BaseMonster::Calculate_HPandDamage(const int& PlayerLevel)
{
	//srand(time(0)); 추후 메인함수에서 한 번만 사용
	int HP_Multiplier = (rand() % 11) + 20;
	int Damage_Multiplier = (rand() % 6) + 5;

	MaxHP = PlayerLevel * HP_Multiplier;
	Damage = PlayerLevel * Damage_Multiplier;
}

// 데미지 적용 메서드
void BaseMonster::TakeDamage(const int& DamagedAmount)
{
	CurrentHP -= DamagedAmount;
	if (CurrentHP < 0)
	{
		CurrentHP = 0;
		IsDead = true;
		return;
	}

	if (CurrentHP <= MaxHP / 2)
	{
		SetState(new EnragedState());
	}
}

// 몬스터 상태 변경 메서드
void BaseMonster::SetState(IState* NewState)
{
	if (CurrentState)
	{
		delete CurrentState;
	}
	CurrentState = NewState;
}
