#pragma once


class Mage : public PlayerCharacter
{
public:
    Mage(const string& name) : PlayerCharacter(name) {}

    void Attack() override
    {
        cout << _name << "이(가) 매직에로우를 시전했습니다!" << endl;
    }
};