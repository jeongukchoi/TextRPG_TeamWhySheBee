#pragma once

class BaseMonster;

class IState
{
public:
	virtual ~IState() = default;
	virtual void HandleState(BaseMonster* Monster) = 0;
};

