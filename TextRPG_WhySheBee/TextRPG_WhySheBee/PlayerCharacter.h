#pragma once

#include <memory>

class PlayerCharacter
{
public:
    PlayerCharacter(const string& name);

    // 스마트 포인터를 사용하여 인스턴스를 관리
    static unique_ptr<PlayerCharacter> GetInstance(const string& name = "", JOB job = JOB::WARRIOR);

    // 몬스터를 공격할 때의 함수
    virtual void Attack(){};

    // 몬스터에게 공격받았을 때의 함수
    void TakeDamage(int amount);

    // 상태 출력 => 공격력 / 체력
    void DisplayStatus() const;

    // 아이템 사용 => 인벤토리와 연계
    void UseItem(int index);

    // 인벤토리에 아이템 추가
    void AddItem(Item* item);

    // 인벤토리에서 아이템 제거
    void RemoveItem(int index);

    // 통합 증가수치
    void IncreaseStat(STATUS stat, int amount);

    // 레벨 업 => 경험치 다 차면 자동레벨업 (몬스터 잡을 때)
    void LevelUp();

    // 기타 Getter 함수
    string GetName() const { return _name; }
    int GetLevel() const { return _level; }
    int GetHealth() const { return _health; }
    int GetMaxHealth() const { return _maxHealth; }
    int GetAttack() const { return _attack; }
    int GetGold() const { return _gold; }
    int GetExperience() const { return _experience; }
    virtual int GetUniqueStat() const { return 0; }

protected:
    static unique_ptr<PlayerCharacter> instance;  // 스마트 포인터로 변경

    string _name;
    int _level;
    int _health;
    int _maxHealth;
    int _attack;
    int _experience;
    int _gold;

    vector<Item*> _inventory;
};
