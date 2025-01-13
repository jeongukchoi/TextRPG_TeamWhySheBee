#pragma once

class BaseMonster
{
protected:
	string Name;
	int MaxHP;
	int CurrentHP;
	int Damage;
	int Speed;
	IState* CurrentState;

public:
	BaseMonster(const string& name, const int& PlayerLevel);
	virtual ~BaseMonster();

	// MaxHP와 Damage 초기화 메서드
	void Calculate_HPandDamage(const int& PlayerLevel);

	// 플레이어에게 공격 당했을 때, 데미지 적용 메서드
	void TakeDamaged(const int& DamagedAmount);

	// 몬스터 상태 변경 메서드
	void SetState(IState* NewState);

	// 분노 상태 스킬 메서드 
	virtual void EnragedSkill() = 0;

	bool IsDead;
	string GetName() { return Name; }
	int GetHealth() { return CurrentHP; }
	int GetDamage() { return Damage; }
	int GetAttackDelay() { return Speed; }
};



