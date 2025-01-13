#include "Framework.h"
#include "EnragedState.h"

void EnragedState::HandleState(BaseMonster* Monster)
{
	cout << Monster->GetName() << "이(가) 분노 상태입니다." << endl;
	Monster->EnragedSkill();
}
