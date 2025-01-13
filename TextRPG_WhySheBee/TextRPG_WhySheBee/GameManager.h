#pragma once

#include <string>

class GameManager {
public:
    GameManager();
    void StartGame();
    void CreateCharacter();
    void GenerateMonster();
    void Battle();
    void DisplayInventory();
    void VisitShop();
    void ShowEnding();

private:
    bool bossCleared;
    // bool over;
};

