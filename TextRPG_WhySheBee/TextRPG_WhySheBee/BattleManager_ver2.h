#pragma once
#include <vector>
class BattleManager
{

private:

	BaseMonster* _currentMonster;
	EnemyFactory* _eFactory;

	PlayerCharacter* _player;

	vector<float> _enemyrand;


	int Choose(const vector<float> probs);

	void deleteMonster();


public:

	BaseMonster* GetMonster() const { return  _currentMonster; };


	BattleManager()
		: _currentMonster(nullptr),
		_eFactory(new EnemyFactory()),
		_player(PlayerCharacter::GetInstance())
	{
		_enemyrand = { 50.0f , 50.0f };
	}
	~BattleManager() {
		delete _currentMonster;
		delete _eFactory;
	}

	bool Battle();

};

