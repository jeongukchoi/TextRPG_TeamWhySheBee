#pragma once
namespace Battle_Ver_1
{
	class BattleManager : public IBattleManager
	{
	private:
		BaseMonster* _currentMonster;
		EnemyFactory* _eFactory;

		//PlayerCharacter* _player;

		void deleteMonster() {
			delete _currentMonster;
			_currentMonster = nullptr;
		}

	public:
		// ������
		BattleManager()
			: _currentMonster(nullptr),
			_eFactory(new EnemyFactory())
			//_player(new PlayerCharacter())
		{
			//_player = PlayerCharacter.GetInstance(name);
		}
		~BattleManager() {
			delete _currentMonster;
			delete _eFactory;
		}

		BaseMonster* GetMonster() const { return  _currentMonster; };

		bool IsCanBattle() const { return _currentMonster->GetHP() > 0; }

		void SummonMonster();

		bool Fight();

	};
}

