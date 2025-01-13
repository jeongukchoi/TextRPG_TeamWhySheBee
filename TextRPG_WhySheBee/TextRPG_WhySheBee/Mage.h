#pragma once


class Mage : public PlayerCharacter
{
public:
    Mage(const string& name);

    void Attack() override ;

    int GetUniqueStat() const override;

    void IncreaseInt(int amount);
   

private:
    int _int;
};