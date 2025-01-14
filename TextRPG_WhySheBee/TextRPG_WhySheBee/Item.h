#pragma once

using namespace std;

class Item
{
public:
    virtual ~Item() {}

    // 아이템 이름
    virtual string GetName() const = 0;
    // 아이템 종류
    virtual ItemType GetType() const = 0;
    // 아이템 가격
    virtual int GetPrice() const = 0;
    // 아이템 ID
    virtual ItemID GetID() const = 0;

    // 아이템이 변경할 스탯
    virtual STATUS GetTargetStat() const = 0;
    // 아이템이 변경할 스탯 스트링
    virtual string GetTargetStatString() const = 0;
    // 아이템이 변경할 스탯 수치
    virtual int GetStatAmount() const = 0;
    // 아이템 정보 출력
    virtual void PrintItemInfo() = 0;
    // 아이템 사용
    virtual void Use() = 0;
};


