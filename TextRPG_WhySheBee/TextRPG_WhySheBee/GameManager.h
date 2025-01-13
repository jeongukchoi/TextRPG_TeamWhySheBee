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

private:
    bool bossCleared;
    // bool over;
};

