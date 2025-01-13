#include "Framework.h"

Mage::Mage(const string& name) :PlayerCharacter(name), _int(1)
{
	_level = 1;
	_health = 100;
	_maxHealth = 100;
	_attack = 50;
	_experience = 0;
	_gold = 0;
	_speed = 4;
}

void Mage::Attack()
{
	cout << _name << "이(가) 매직에로우를 시전했습니다!" << endl;
}

int Mage::GetUniqueStat() const
{
	return _int;  // Mage 클래스에서는 _int 값을 반환
}

void Mage::IncreaseInt(int amount)
{
	_int += amount;
	cout << "마법사의 INT가 " << amount << "만큼 증가했습니다! 현재 INT: " << _int << endl;
}
