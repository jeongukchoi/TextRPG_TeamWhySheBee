#pragma once

class BaseMonster;

class IState
{
public:
	virtual ~IState() = default;
	virtual string HandleState(BaseMonster* Monster) = 0;
};


