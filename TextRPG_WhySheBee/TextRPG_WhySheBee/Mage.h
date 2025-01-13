#pragma once


class Mage : public PlayerCharacter
{
public:
    Mage(const string& name);


    int GetUniqueStat() const override;

    void IncreaseInt(int amount);

    int Attack() override;
    int RandomAttack();

private:
    int _int;
};