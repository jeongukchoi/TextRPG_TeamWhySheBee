#pragma once

#include <string>

class GameManager {
public:
    GameManager();
    void StartGame();
    void CreateCharacter();
    void DisplayInventory();
    void VisitShop();
    void ShowEnding();
    void Battle();
private:
    bool bossCleared;
    // bool over;
};
