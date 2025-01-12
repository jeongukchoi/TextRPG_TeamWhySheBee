#pragma once

#include "GameManager.h"
#include "Item.h"
#include "PlayerCharacter.h"
#include "AttackBoost.h"
#include "HealthPotion.h"
#include "ItemManager.h"
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

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <iomanip>
#include <random>
#include <cstdlib>
#include <ctime>
#include <memory>	

using namespace std;