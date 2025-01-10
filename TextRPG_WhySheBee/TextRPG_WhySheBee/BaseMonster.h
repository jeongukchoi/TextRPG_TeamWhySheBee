#pragma once
class BaseMonster
{
protected:
	string Name;
	int MaxHP;
	int CurrentHP;
	int Damage;
	bool IsDead;
	IState* CurrentState;

public:
	BaseMonster(const string& name, const int& PlayerLevel);
	virtual ~BaseMonster();

	// MaxHP와 Damage 초기화 메서드
	void Calculate_HPandDamage(const int& PlayerLevel);

	// 플레이어에게 공격 당했을 때, 데미지 적용 메서드
	void TakeDamage(const int& DamagedAmount);

	// 몬스터 상태 변경 메서드
	void SetState(IState* NewState);

	// 고유 스킬 순수 가상 메서드 / 추후 상태 패턴으로 구현으로 바뀔 예정입니다.
	virtual void UseSkill() = 0;

	string GetName() { return Name; }
	int GetHP() { return CurrentHP; }
	int GetDamage() { return Damage; }
};


