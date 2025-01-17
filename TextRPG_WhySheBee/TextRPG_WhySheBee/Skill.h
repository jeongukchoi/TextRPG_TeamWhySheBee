#pragma once

class Skill 
{
public:
	
	~Skill() {}

	virtual int Activate(int attackPower,int stat) = 0;
	virtual string GetName() { return _skillName; }

protected:
	string _skillName;

};