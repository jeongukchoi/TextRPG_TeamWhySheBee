#pragma once


class Warrior : public PlayerCharacter
{

public:
    Warrior(const string& name);

    int Attack() override;

    int GetUniqueStat();
    void IncreaseStr(int amount);

    int RandomAttack();

private:
    int _str;
};