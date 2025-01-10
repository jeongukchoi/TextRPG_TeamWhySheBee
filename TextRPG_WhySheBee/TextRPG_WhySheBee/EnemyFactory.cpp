#include "Framework.h"
#include "EnemyFactory.h"

BaseMonster* EnemyFactory::getMonster(int id, int level)
{
	switch (id)
	{
	case 1:
		return new Goblin("Goblin", level);

	case 2:
		return new Orc("Orc", level);

	default:
		return nullptr;
		break;
	}
}