#include "Framework.h"
#include "Orc.h"

void Orc::UseSkill()
{
	cout << GetName() << "." << endl;
	CurrentHP += (MaxHP - CurrentHP) / 2;
}