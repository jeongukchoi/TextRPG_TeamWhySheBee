#include "Framework.h"

Warrior::Warrior(const string& name) : PlayerCharacter(name),_str(1)
{
	_level = 1;
	_health = 200;
	_maxHealth = 200;
	_attack = 30;
	_experience = 0;
	_gold = 0;
	_attackDelay = 2;
	_job = WARRIOR;
}

int Warrior::Attack() 
{
	int totalDamage = 0;
	totalDamage = RandomAttack();
	return totalDamage;
}

int Warrior::GetUniqueStat()
{
	return _str;
}

void Warrior::IncreaseStr(int amount)
{
	_str += amount;
	//cout << "전사의 STR이 " << amount << "만큼 증가했습니다! 현재 STR: " << _str << endl;
}

int Warrior::RandomAttack()
{
	int randomWeight = (rand() % 100) + 1;
	int Damage = 0;
	Skill* _randomSkill = nullptr;
	if (randomWeight <= 50)
	{
		cout << "기본 공격!!" << endl;
		Damage = _attack; // 기본 공격은 _attack 값
		cout << "데미지: " << Damage << endl;
		return Damage;
	}
	else if (randomWeight <= 80)
	{
		_randomSkill = new PowerStrike();
	}
	else
	{
		_randomSkill = new LastStrike();
	}

	Damage = _randomSkill->Activate(_attack,_str);

	cout << "데미지: " << Damage << endl;

	return Damage;
}

