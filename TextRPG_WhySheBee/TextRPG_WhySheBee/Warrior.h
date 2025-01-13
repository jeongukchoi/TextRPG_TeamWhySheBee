#pragma once


class Warrior : public PlayerCharacter
{
public:
    Warrior(const string& name) : PlayerCharacter(name) {}

    void Attack() override
    {
        cout << _name << "이(가) 파워스트라이크를 시전했습니다!" << endl;
    }
};