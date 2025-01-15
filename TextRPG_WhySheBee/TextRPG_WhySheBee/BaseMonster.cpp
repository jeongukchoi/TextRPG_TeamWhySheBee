#include "Framework.h"
#include "BaseMonster.h"

BaseMonster::BaseMonster(const string& name, const int& PlayerLevel)
{
	Name = name;
	IsDead = false;
	Speed = 6;
	Damage = 10;
	MaxHP = 100;
	CurrentState = new NormalState(); //상태 객체 동적 생성

	Calculate_HPandDamage(PlayerLevel);

	CurrentHP = MaxHP;
}

BaseMonster::~BaseMonster()
{
	delete CurrentState; // 상태 객체 동적 해제
}

// MaxHP와 Damage 초기화 메서드
void BaseMonster::Calculate_HPandDamage(const int& PlayerLevel)
{
	int HP_Multiplier = (rand() % 51) + 50;
	int Damage_Multiplier = (rand() % 5) + 10;

	MaxHP += PlayerLevel * HP_Multiplier;
	Damage += PlayerLevel * Damage_Multiplier;
}

// 데미지 적용 메서드
string BaseMonster::TakeDamaged(const int& DamagedAmount)
{
	CurrentHP -= DamagedAmount;
	if (CurrentHP <= 0)
	{
		CurrentHP = 0;
		IsDead = true;
		return;
	}

	cout << Name << " 의 체력이 : " << DamagedAmount << "만큼 감소했습니다." << endl;

	if (CurrentHP <= MaxHP / 2 && dynamic_cast<NormalState*>(CurrentState) != nullptr	)
	{
		SetState(new EnragedState());

		return CurrentState->HandleState(this);
	}
	return "";
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

