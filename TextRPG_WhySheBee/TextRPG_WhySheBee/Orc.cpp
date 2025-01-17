#include "Framework.h"

string Orc::EnragedSkill()
{
	CurrentHP += (MaxHP - CurrentHP) / 2;
	return Name + "가 잃은 체력의 절반을 회복합니다!";
}


