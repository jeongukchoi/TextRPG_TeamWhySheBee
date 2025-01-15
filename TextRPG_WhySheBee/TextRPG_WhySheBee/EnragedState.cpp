#include "Framework.h"
#include "EnragedState.h"

string EnragedState::HandleState(BaseMonster* Monster)
{
	cout << Monster->GetName() << "이(가) 분노 상태입니다." << endl;
	
	string SkillMent = Monster->EnragedSkill();

	return SkillMent;
}

