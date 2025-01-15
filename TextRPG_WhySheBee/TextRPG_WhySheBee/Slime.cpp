#include "Framework.h"

string Slime::EnragedSkill()
{
	CurrentHP += Player->GetAttack();
	return Name + "이 플레이어의 방금 공격을 무효화 했습니다!";
}

