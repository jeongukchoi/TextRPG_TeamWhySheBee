#include "Framework.h"

unique_ptr<PlayerCharacter> PlayerCharacter::instance = nullptr;

unique_ptr<PlayerCharacter>& PlayerCharacter::GetInstance(const string& name, JOB job)
{
    if (!instance)
    {
        switch (job)
        {
        case JOB::WARRIOR:
            instance = make_unique<Warrior>(name);
            break;
        case JOB::MAGE:
            instance = make_unique<Mage>(name);
            break;
        default:
            instance = make_unique<PlayerCharacter>(name); // 기본 캐릭터
            break;
        }
    }
    return instance; //주소값만 리턴해준다.
}

PlayerCharacter::PlayerCharacter(const string& name)
    : _name(name), _level(1), _health(200), _maxHealth(200), _attack(30), _experience(0), _gold(0),_attackDelay(0),_job(WARRIOR)
{
}

void PlayerCharacter::TakeDamage(int amount)
{
    _health -= amount;
    if (_health <= 0)
    {
        _health = 0;
    }
   /* cout << "플레이어의 체력이 : " << amount << "만큼 감소했습니다." << endl;
    cout << "현재 체력 : " << _health << endl;*/
}

void PlayerCharacter::DisplayStatus() const
{
    ColorPrinter color;
    ConsoleManager printer;
    printer.SetCursorPosition(2, 20);
    
    cout << "===== " << color.ColoredText(_name, CYAN) << "의 상태 =====" << endl;
    printer.SetCursorPosition(2, 21);
    cout << "레벨: " << _level << ", 경험치: " << _experience << "/ " << _level * 10 << "  " << endl;
    printer.SetCursorPosition(2, 22);
    if (_health < _maxHealth*0.5f)
    {
        cout << "체력: " << color.ColoredText(to_string(_health), RED) << "/" << color.ColoredText(to_string(_maxHealth), BLUE)
            << ", 공격력: " << _attack << "  " << endl;
    }
    else
    {
        cout << "체력: " << color.ColoredText(to_string(_health), BLUE) << "/" << color.ColoredText(to_string(_maxHealth), BLUE) 
            << ", 공격력: " << _attack << "  " << endl;
    }
    printer.SetCursorPosition(2, 23);
    cout << "골드: " << color.ColoredText(to_string(_gold), YELLOW) << endl;
    printer.DrawRectangle(1, 19, 30, 8);
    printer.SetCursorPosition(0, 0);
    //system("cls");
}

void PlayerCharacter::IncreaseStat(STATUS stat, int amount)
{


    switch (stat)
    {
    case HP:
        _health += amount;
        if (_health > _maxHealth) _health = _maxHealth;
        //cout << "체력이 " << amount << "만큼 증가했습니다! 현재 체력: " << _health << "/" << _maxHealth << endl;
        break;
    case MAXHP:
        _maxHealth += amount;
        //cout << "최대 체력이 " << amount << "만큼 증가했습니다! 현재 최대 체력: " << _maxHealth << endl;
        break;
    case ATTACK:
        _attack += amount;
        //cout << "공격력이 " << amount << "만큼 증가했습니다! 현재 공격력: " << _attack << endl;
        break;
    case GOLD:
        _gold += amount;
        //cout << "골드가 " << amount << "만큼 증가했습니다! 현재 골드: " << _gold << endl;
        break;
    case EXP:
        _experience += amount;
        //cout << "경험치가 " << amount << "만큼 증가했습니다! 현재 경험치: " << _experience << "/100" << endl;

        // 레벨 업 확인
        while (_experience >= _level * 10)
        {
            _experience -= _level * 10;
            LevelUp(); // 레벨 업에 필요한 경험치 차감
        }
        break;
    case STR:
            // 자식 클래스에서 특별히 처리할 수 있도록 함
            if (Warrior* warrior = dynamic_cast<Warrior*>(this))
            {
                warrior->IncreaseStr(amount);  // Mage일 경우에만 INT 증가
            }
            break;
    case INTELLGENCE:
        // 자식 클래스에서 특별히 처리할 수 있도록 함
        if (Mage* mage = dynamic_cast<Mage*>(this))
        {
            mage->IncreaseInt(amount);  // Mage일 경우에만 INT 증가
        }
        break;
    case SPEED:
        _attackDelay += amount;
        //cout << "속도가 " << amount << "만큼 증가했습니다! 현재 속도: " << _gold << endl;
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
    // 아이템 사용 후 제거
}

