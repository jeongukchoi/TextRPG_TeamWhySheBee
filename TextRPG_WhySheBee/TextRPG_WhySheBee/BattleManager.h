#pragma once

#include "PlayerCharacter.h"
#include "ItemManager.h"
#include "Inventory.h"
#include "ConsoleManager.h"
#include <memory>
#include "ConsoleManager.h"

class BattleManager
{
private:
	PlayerCharacter* Player;
	Inventory* PlayerInventory;
	ItemManager Item_Manager;
	unique_ptr<BaseMonster> Monster;
	ConsoleManager Console;
	int PlayerLevel;
	int PlayerAttackDelay;
	int CurrentAttackDelay;
	int CurrentTextYposition = 0;
	int NextTextYPosition = 0;
	vector<int> MonsterExp{ 5,10,15,15,15,20,20,20,20 };
	vector<string> Texts;

public:
	BattleManager() : Player(PlayerCharacter::GetPlayer()), PlayerInventory(Inventory::GetInstance()), PlayerLevel(1), PlayerAttackDelay(Player->GetAttackDelay()) {}


	// 전투 메서드(플레이어의 승,패 여부를 반환합니다)
	bool Battle();

	BaseMonster* GetMonster() const { return  Monster.get(); }

private:
	// 몬스터 생성 메서드
	void CreateMonster();

	// 플레이어 공격 메서드
	void PlayerAttack();
	// 몬스터 공격 메서드
	void MonsterAttack();

	// 플레이어 사망 체크 메서드
	bool IsPlayerDead();
	// 몬스터 사망 체크 메서드
	bool IsMonsterDead();

	// 몬스터 보상 메서드
	void GetRewards();
	// 확률적으로 아이템 드롭 및 인벤토리 저장 메서드
	void GetRandomItem();
	// 확률적으로 아이템 사용 메서드
	void RandomUseItem();
	// 공격 최소 데미지 최고 데미지 변경
	float AttackMinaMax(float min, float max);
	// 전투 출력
	void PrintBattle();
	// 몬스터 스텟 출력 메서드
	void DisplayMonsterStats();
	//텍스트저장
	void CheckAndGetString(string txt);
};


