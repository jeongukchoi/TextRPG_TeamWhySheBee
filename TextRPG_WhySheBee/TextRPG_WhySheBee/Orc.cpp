#include "Framework.h"

void Orc::EnragedSkill()
{
	cout << Name << "가 잃은 체력의 절반을 회복합니다!" << endl;
	CurrentHP += (MaxHP - CurrentHP) / 2;
}


