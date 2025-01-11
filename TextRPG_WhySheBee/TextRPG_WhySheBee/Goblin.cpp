#include "Framework.h"

void Goblin::EnragedSkill()
{
	cout << this->GetName() << "이 신체를 강화시켜 데미지가 2배 상승합니다!" << endl;
	Damage *= 2;
}