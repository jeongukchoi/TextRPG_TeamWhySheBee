#include "Framework.h"

Mage::Mage(const string& name) :PlayerCharacter(name), _int(1)
{
	_level = 1;
	_health = 150;
	_maxHealth = 150;
	_attack = 15;
	_experience = 0;
	_gold = 0;
	_attackDelay = 3;
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
		cout << "기본 공격!!" << endl;
		Damage = _attack; 
		cout << "데미지: " << Damage << endl;
		return Damage;
	}
	else if (randomWeight <= 80)
	{
		cout << _name << "이(가) 매직에로우를 시전했습니다!" << endl;
		Damage = _attack + _int * 70; // 스킬은 공격력의 1.5배 + 알파
		_randomSkill = new MagicArrow();
	}
	else
	{
		cout << "궁극기를 사용합니다!" << endl;
		Damage = _attack + _int * 200; // 궁극기는 공격력의 3배 + 알파 // tnwjd 
		_randomSkill = new Meteor();
	}	

	Damage = _randomSkill->Activate(_attack, _int);

	cout << "데미지: " << Damage << endl;
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
