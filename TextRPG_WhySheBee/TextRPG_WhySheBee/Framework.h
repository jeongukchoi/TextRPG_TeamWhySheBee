#pragma once


// 텍스트 색상 정의 (밝은 색상)
#define BLACK   "\033[1;30m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define MAGENTA "\033[1;35m"
#define CYAN    "\033[1;36m"
#define WHITE   "\033[1;37m"

// 색상 초기화
#define RESET   "\033[0m"

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <iomanip>
#include <random>
#include <cstdlib>
#include <ctime>
#include <memory>
#include <unordered_map>
#include <windows.h>
#include <sstream>

using namespace std;


//초기포함헤더
#include "Enums.h"

#include "ColorPrinter.h"


//플레이어관련

#include "Skill.h"
#include "PowerStrike.h"
#include "MagicArrow.h"
#include "Meteor.h"
#include "LastStrike.h"



#include "PlayerCharacter.h"
#include "Warrior.h"
#include "Mage.h"

//인벤토리&상점

#include "Item.h"
#include "Equipment.h"
#include "EquipmentDecorator.h"
#include "SwordUpgrade.h"
#include "ArmorUpgrade.h"
#include "Sword.h"
#include "Armor.h"
#include "AttackBoost.h"
#include "HealthPotion.h"
#include "UniquePotion.h"
#include "ItemManager.h"
#include "Inventory.h"
#include "Shop.h"


//몬스터관련
#include "IState.h"
#include "NormalState.h"
#include "EnragedState.h"
#include "BaseMonster.h"
#include "Goblin.h"
#include "Orc.h"
#include "Troll.h"
#include "Slime.h"
#include "BossMonster.h"
#include "EnemyFactory.h"
#include "BattleManager.h"

#include "GameManager.h"


