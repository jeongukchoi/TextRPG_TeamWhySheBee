#include "Framework.h"
#include "BattleManager_ver2.h"

void BattleManager::deleteMonster() {
	delete _currentMonster;
	_currentMonster = nullptr;
}

/*
int BattleManager::Choose(const vector<float> probs)
{
	float total = 0;

	for (float i : probs)
	{
		total += i;
	}

	float randomPoint = static_cast<float>(rand()) / RAND_MAX * total;


	********여기에 while 이나 for loop 조건문이 빠진 것 같아요!!**********
	{
		if (randomPoint < probs[i])
		{
			return i;
		}
		else {
			randomPoint -= probs[i];
		}
	}


}
*/




bool BattleManager::Battle() {
	if (_player == nullptr)
	{
		return false;
	}

	if (_currentMonster == nullptr)
	{
		//_currentMonster = _eFactory->getMonster(Choose(_enemyrand), _player.GetLevel());
	}


	if (_player->GetHealth() <= 0 || _currentMonster->GetHP() <= 0)
	{
		return false;
	}

	if (_player->GetHealth() <= _currentMonster->GetDamage())
	{
		_player->UseItem(0);
	}




	_currentMonster->TakeDamage(_player->GetAttack());

	if (_currentMonster->GetHP() <= 0)
	{

		deleteMonster();

		_player->IncreaseStat(EXP, 50);
		//player->AddItem(new Item()); 
		return false;
	}


	if (_player->GetHealth() <= 0)
	{
		return false;
	}


	return true;
}