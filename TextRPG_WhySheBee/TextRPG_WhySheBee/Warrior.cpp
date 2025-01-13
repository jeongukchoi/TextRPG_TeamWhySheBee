#include "Framework.h"

Warrior::Warrior(const string& name) : PlayerCharacter(name)
{
	_level = 1;
	_health = 200;
	_maxHealth = 200;
	_attack = 30;
	_experience = 0;
	_gold = 0;
	_speed = 2;
}

void Warrior::Attack()
{
	cout << _name << "이(가) 파워스트라이크를 시전했습니다!" << endl;
}
