#include "Framework.h"

void Slime::EnragedSkill()
{
	cout << this->GetName() << "이 플레이어의 방금 공격을 무효화 했습니다!" << endl;
	
	CurrentHP += Player->GetAttack();
}

