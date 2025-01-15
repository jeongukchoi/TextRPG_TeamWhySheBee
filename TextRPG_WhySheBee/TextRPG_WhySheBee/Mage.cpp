#include "Framework.h"

Mage::Mage(const string& name) :PlayerCharacter(name), _int(1)
{
	_level = 1;
	_health = 150;
	_maxHealth = 150;
	_attack = 30;
	_experience = 0;
	_gold = 0;
	_attackDelay = 2;
	_job = MAGE;
}

int Mage::Attack()
{
	int totalDamage = 0;
	totalDamage = RandomAttack();
	return totalDamage;
}

int Mage::RandomAttack()
{
	int randomWeight = (rand() % 100) + 1;
	int Damage = 0;

	Skill* _randomSkill = nullptr;
	if (randomWeight <= 40)
	{
		Damage = _attack; 
		_skillName = "일반공격";
		return Damage;
	}
	else if (randomWeight <= 80)
	{
		_randomSkill = new MagicArrow();
	}
	else
	{
		_randomSkill = new Meteor();
	}	

	Damage = _randomSkill->Activate(_attack, _int);
	_skillName = _randomSkill->GetName();

	delete _randomSkill;
	return Damage;
}

int Mage::GetUniqueStat() const
{
	return _int;  // Mage 클래스에서는 _int 값을 반환
}

void Mage::IncreaseInt(int amount)
{
	_int += amount;
	//cout << "마법사의 INT가 " << amount << "만큼 증가했습니다! 현재 INT: " << _int << endl;
}
