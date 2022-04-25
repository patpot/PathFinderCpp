#pragma once
//======================================================================================
//Header file for bots: initially cBotRandom is defined here, but other bot classes
//can go here too
//
//(c) Patrick Dickinson, University of Lincoln, School of Computer Science, 2020
//======================================================================================

#include "botbase.h"
#include <cmath>
#include <tuple>

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

class cDijkstra : public cBotBase {
	public:
	bool closed[GRIDWIDTH][GRIDHEIGHT]; //whether or not location is closed
	float cost[GRIDWIDTH][GRIDHEIGHT]; //cost value for each location
	int linkX[GRIDWIDTH][GRIDHEIGHT]; //link X coord for each location
	int linkY[GRIDWIDTH][GRIDHEIGHT]; //link Y coord for each location
	bool inPath[GRIDWIDTH][GRIDHEIGHT]; //whether or not a location is in 
	
	bool completed;
	cDijkstra() { completed = false; }
	virtual void Build();
	virtual void ChooseNextGridPosition() { };
};

class cAStar : public cDijkstra
{
public:
	virtual void Build();
	virtual void ChooseNextGridPosition();

	std::pair<int, int> path[100];
	int arrayPos;
};


extern cDijkstra gDijkstra;
extern cAStar gAStar;
