#include "Framework.h"
#include "PlayerCharacter.h"

PlayerCharacter* PlayerCharacter::instance = nullptr;

PlayerCharacter* PlayerCharacter::GetInstance(const string& name)
{
    if (!instance)
    {
        instance = new PlayerCharacter(name);
    }
    return instance;
}

PlayerCharacter::PlayerCharacter(const string& name)
    : _name(name), _level(1), _health(200), _maxHealth(200), _attack(30), _experience(0), _gold(0)
{
}

void PlayerCharacter::DisplayStatus() const
{
    cout << "===== " << _name << "의 상태 =====" << endl;
    cout << "레벨: " << _level << ", 경험치: " << _experience << "/100" << endl;
    cout << "체력: " << _health << "/" << _maxHealth << ", 공격력: " << _attack << endl;
    cout << "골드: " << _gold << endl;
    cout << "======================" << endl;
}

void PlayerCharacter::IncreaseStat(STATUS stat, int amount)
{
    switch (stat)
    {
    case HP:
    {
        _health += amount;
        if (_health > _maxHealth) _health = _maxHealth;
        cout << "체력이 " << amount << "만큼 증가했습니다! 현재 체력: " << _health << "/" << _maxHealth << endl;
    }
    break;

    case MAXHP:
    {
        _maxHealth += amount;
        cout << "최대 체력이 " << amount << "만큼 증가했습니다! 현재 최대 체력: " << _maxHealth << endl;
    }
    break;


    case ATTACK:
    {
        _attack += amount;
        cout << "공격력이 " << amount << "만큼 증가했습니다! 현재 공격력: " << _attack << endl;
    }
    break;

    case GOLD:
    {
        _gold += amount;
        cout << "골드가 " << amount << "만큼 증가했습니다! 현재 골드: " << _gold << endl;
    }
    break;

    case EXP:
    {
        _experience += amount;
        cout << "경험치가 " << amount << "만큼 증가했습니다! 현재 경험치: " << _experience << "/100" << endl;

        // 레벨 업 확인
        while (_experience >= 100)
        {
            LevelUp();
            _experience -= 100; // 레벨 업에 필요한 경험치 차감
        }
    }
    break;

    default:
        cout << "알 수 없는 Stat 값입니다!" << endl;
        break;
    }

}

void PlayerCharacter::LevelUp()
{
    if (_level >= 10)
    {
        cout << "최대 레벨에 도달했습니다!" << endl;
        return;
    }
    _level++;
    _maxHealth += (_level * 20);
    _attack += (_level * 5);
    _health = _maxHealth; // 체력 완전 회복
    _experience = 0; // 경험치 초기화
    cout << "레벨업! 현재 레벨: " << _level << endl;
}

void PlayerCharacter::UseItem(int index)
{
    
    if (index < 0 || index >= _inventory.size())
    {
        cout << "잘못된 인덱스입니다!" << endl;
        return;
    }

    Item* item = _inventory[index];

    item->Use();

    // 아이템 사용 후 제거
    RemoveItem(index);
    
    return;
}
void PlayerCharacter::AddItem(Item* item)
{

    _inventory.push_back(item);
    cout << item->GetName() << "을(를) 획득했습니다!" << endl;

}

void PlayerCharacter::RemoveItem(int index)
{
    
    if (index < 0 || index >= _inventory.size())
    {
        throw out_of_range("잘못된 인덱스입니다!");
    }
    _inventory.erase(_inventory.begin() + index);
    
    return;
}


