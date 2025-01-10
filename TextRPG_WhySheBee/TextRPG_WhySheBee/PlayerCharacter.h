#pragma once
#include <vector>

enum STATUS
{
    HP = 0,
    MAXHP,
    ATTACK,
    GOLD,
    EXP
};

class PlayerCharacter
{
public:
    PlayerCharacter(const string& name);

    static PlayerCharacter* GetInstance(const string& name = "");

    // 상태 출력 => 공격력 / 체력
    void DisplayStatus() const;


    // 아이템 사용 => 인벤토리와 연계
    void UseItem(int index);
    //// 인벤토리에 아이템 추가
    void AddItem(Item* item);

    //// 인벤토리에서 아이템 제거
    void RemoveItem(int index);

    //통합 증가수치
    void IncreaseStat(STATUS stat, int amount);
    // 레벨 업 => 경험치 다차면 자동레벨업 (몬스터잡을때)
    void LevelUp();


    // 기타 Getter함수 (다른분 참조용)
    int GetLevel() const { return _level; }
    int GetHealth() const { return _health; }
    int GetMaxHealth() const { return _maxHealth; }
    int GetAttack() const { return _attack; }
    int GetGold() const { return _gold; }
    int GetExperience() const { return _experience; }



private:
    static PlayerCharacter* instance; // 싱글톤 인스턴스

    string _name;
    int _level;
    int _health;
    int _maxHealth;
    int _attack;
    int _experience;
    int _gold;

    vector<Item*> _inventory;
};
