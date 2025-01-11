#include "Framework.h"

void Troll::EnragedSkill()
{
	cout << this->GetName() << "이 괴성을 지르며 최대 체력으로 회복합니다." << endl;

	CurrentHP = MaxHP;
}
