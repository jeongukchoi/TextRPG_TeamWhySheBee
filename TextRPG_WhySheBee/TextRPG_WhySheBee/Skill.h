#pragma once

class Skill 
{
public:
	
	~Skill() {}

	virtual int Activate(int attackPower,int stat) = 0;


};