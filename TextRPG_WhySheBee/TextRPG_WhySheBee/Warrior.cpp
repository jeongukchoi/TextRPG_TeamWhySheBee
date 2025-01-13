#include "Framework.h"

Warrior::Warrior(const string& name) : PlayerCharacter(name),_str(1)
{
	_level = 1;
	_health = 200;
	_maxHealth = 200;
	_attack = 30;
	_experience = 0;
	_gold = 0;
	_speed = 2;
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
	cout << "전사의 STR이 " << amount << "만큼 증가했습니다! 현재 STR: " << _str << endl;
}

int Warrior::RandomAttack()
{
	int randomWeight = (rand() % 100) + 1;
	int Damage = 0;
	if (randomWeight <= 50)
	{
		cout << "기본 공격을 사용합니다!" << endl;
		Damage = _attack; // 기본 공격은 _attack 값
	}
	else if (randomWeight <= 80)
	{
		cout << "스킬(파워스트라이크!)을 사용합니다!" << endl;
		Damage = _attack * 1.5 + _str * 5; // 스킬은 공격력의 1.5배
	}
	else
	{
		cout << "궁극기를 사용합니다!" << endl;
		Damage = _attack * 2 + _str*10; // 궁극기는 공격력의 3배
	}

	cout << "총 데미지: " << Damage << endl;
	return Damage;
}

