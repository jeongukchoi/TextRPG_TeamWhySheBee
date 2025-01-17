#pragma once

#include <string>

class GameManager {
public:
    GameManager();
    void StartGame();
    void CreateCharacter();
    void Battle();
    void DisplayInventory();
    void VisitShop(Shop* shop);
    void ShowEnding();
private:
    bool over;
};

