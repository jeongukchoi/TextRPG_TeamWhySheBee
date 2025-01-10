#include "Framework.h"
#include "Goblin.h"

void Goblin::UseSkill()
{
	cout << GetName() << "." << endl;
	Damage *= 2;
}