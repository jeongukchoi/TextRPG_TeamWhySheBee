#pragma once

using namespace std;

class PlayerCharacter;

class Item
{
public:
    // 아이템 이름
    virtual string GetName() const = 0;
    // 아이템이 변경할 스탯
    virtual STATUS GetTargetStat() const = 0;
    // 아이템이 변경할 스탯 수치
    virtual int GetStatAmount() const = 0;
    // 아이템 정보 출력
    virtual void PrintItemInfo() = 0;

    virtual void Use(PlayerCharacter* character) = 0;
};

