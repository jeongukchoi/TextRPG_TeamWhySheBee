#pragma once


class Warrior : public PlayerCharacter
{

public:
    Warrior(const string& name);

    void Attack() override;
};