#pragma once
class IBattleManager
{
public:
	virtual ~IBattleManager() {}
	virtual bool Battle() = 0;
};

