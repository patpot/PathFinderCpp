#include "bots.h"
#include <cmath>
#include <stdlib.h>
using namespace std;

void cDijkstra::Build() {
	for (int i = 0; i < GRIDWIDTH; i++) {
		for (int j = 0; j < GRIDHEIGHT; j++) {
			closed[i][j] = false; // node is open
			cost[i][j] = 1000000.0f; // node is unreachable
			linkX[i][j] = -1; // node has no link
			linkY[i][j] = -1; // node has no link
			inPath[i][j] = false; // node is not in path
		}
	}

	int botX = PositionX();
	int botY = PositionY();
	cost[botX][botY] = 0;

	// find grid location with the lowest cost
	while (true) {
		float lowestCost = 1000000.0f;
		int lowestX = -1;
		int lowestY = -1;
		for (int i = 0; i < GRIDWIDTH; i++) {
			for (int j = 0; j < GRIDHEIGHT; j++) {
				if (cost[i][j] < lowestCost && !closed[i][j]) {
					lowestCost = cost[i][j];
					lowestX = i;
					lowestY = j;
				}
			}
		}
		// close this lowest cost node
		closed[lowestX][lowestY] = true;

		// recalculate costs for nodes surrounding our lowest cost node in a 1 by 1 square
		int x = lowestX - 1;
		int y = lowestY - 1;
		for (int xOffset = 0; xOffset < 3; xOffset++) {
			for (int yOffset = 0; yOffset < 3; yOffset++) {
				int xPos = x + xOffset;
				int yPos = y + yOffset;
				if (gLevel.isValid(xPos, yPos) && !closed[xPos][yPos]) {
					float newCost = cost[lowestX][lowestY] + 1.0f;
					// change nodes at a diagonal from the centre point lowestX lowestY by 1.4f
					if (xOffset % 2 == 0 && yOffset % 2 == 0) {
						newCost += 0.4f;
					}

					if (newCost < cost[xPos][yPos]) {
						cost[xPos][yPos] = newCost;
						linkX[xPos][yPos] = lowestX;
						linkY[xPos][yPos] = lowestY;
					}
				}
			}
		}

		if (closed[gTarget.PositionX()][gTarget.PositionY()])
			break;
	}

	bool done = false; //set to true when we are back at the bot position
	int nextClosedX = gTarget.PositionX(); //start of path
	int nextClosedY = gTarget.PositionY(); //start of path
	while (!done)
	{
		inPath[nextClosedX][nextClosedY] = true;
		int tmpX = nextClosedX;
		int tmpY = nextClosedY;
		nextClosedX = linkX[tmpX][tmpY];
		nextClosedY = linkY[tmpX][tmpY];
		if ((nextClosedX == PositionX()) && (nextClosedY ==
			PositionY())) done = true;
	}
	
	completed = true;
}
cDijkstra gDijkstra;

void cAStar::Build() {
	for (int i = 0; i < GRIDWIDTH; i++) {
		for (int j = 0; j < GRIDHEIGHT; j++) {
			closed[i][j] = false; // node is open
			cost[i][j] = 1000000.0f; // node is unreachable
			linkX[i][j] = -1; // node has no link
			linkY[i][j] = -1; // node has no link
			inPath[i][j] = false; // node is not in path
		}
	}

	int botX = PositionX();
	int botY = PositionY();
	cost[botX][botY] = 0;

	// find grid location with the lowest cost
	while (true) {
		float lowestCost = 1000000.0f;
		int lowestX = -1;
		int lowestY = -1;
		for (int i = 0; i < GRIDWIDTH; i++) {
			for (int j = 0; j < GRIDHEIGHT; j++) {
				float heuristic = fabs(gTarget.PositionX() - i) + fabs(gTarget.PositionY() - j);
				float totalCost = cost[i][j] + heuristic;
				if (totalCost < lowestCost && !closed[i][j]) {
					lowestCost = totalCost;
					lowestX = i;
					lowestY = j;
				}
			}
		}
		// close this lowest cost node
		closed[lowestX][lowestY] = true;

		// recalculate costs for nodes surrounding our lowest cost node in a 1 by 1 square
		int x = lowestX - 1;
		int y = lowestY - 1;
		for (int xOffset = 0; xOffset < 3; xOffset++) {
			for (int yOffset = 0; yOffset < 3; yOffset++) {
				int xPos = x + xOffset;
				int yPos = y + yOffset;
				if (gLevel.isValid(xPos, yPos) && !closed[xPos][yPos]) {
					float newCost = cost[lowestX][lowestY] + 1.0f;
					// change nodes at a diagonal from the centre point lowestX lowestY by 1.4f
					if (xOffset % 2 == 0 && yOffset % 2 == 0) {
						newCost += 0.4f;
					}

					if (newCost < cost[xPos][yPos]) {
						cost[xPos][yPos] = newCost;
						linkX[xPos][yPos] = lowestX;
						linkY[xPos][yPos] = lowestY;
					}
				}
			}
		}

		if (closed[gTarget.PositionX()][gTarget.PositionY()])
			break;
	}

	bool done = false; //set to true when we are back at the bot position
	int nextClosedX = gTarget.PositionX(); //start of path
	int nextClosedY = gTarget.PositionY(); //start of path
	while (!done)
	{
		path[++arrayPos] = std::make_pair(nextClosedX, nextClosedY);
		inPath[nextClosedX][nextClosedY] = true;
		int tmpX = nextClosedX;
		int tmpY = nextClosedY;
		nextClosedX = linkX[tmpX][tmpY];
		nextClosedY = linkY[tmpX][tmpY];
		if ((nextClosedX == PositionX()) && (nextClosedY ==
			PositionY())) done = true;
	}

	completed = true;
}

void cAStar::ChooseNextGridPosition() {
	if (arrayPos >= 0) {
		pair<int, int> coords = path[arrayPos];
		SetNext(coords.first, coords.second, gLevel);
		arrayPos--;
	}
}

cAStar gAStar;