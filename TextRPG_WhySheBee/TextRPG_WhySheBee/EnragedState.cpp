#include "Framework.h"
#include "EnragedState.h"

string EnragedState::HandleState(BaseMonster* Monster)
{
	string SkillMent = Monster->EnragedSkill();
	return SkillMent;
}

