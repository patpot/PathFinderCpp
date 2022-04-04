#pragma once
//======================================================================================
//Header file for bots: initially cBotRandom is defined here, but other bot classes
//can go here too
//
//(c) Patrick Dickinson, University of Lincoln, School of Computer Science, 2020
//======================================================================================

#include "botbase.h"
#include <cmath>

class cBotRandom : public cBotBase
{
	virtual void ChooseNextGridPosition();
};

class cBotSimple2 : public cBotBase
{
public:
	cBotSimple2();
	virtual void ChooseNextGridPosition();
	void CalculateMoveDir();
	bool IsDirectionBlacklisted(float val);
private:
	bool correctPosition = false;
	float moveDir;
	float blacklistDir[8];
	int arrayPos = 0;
};