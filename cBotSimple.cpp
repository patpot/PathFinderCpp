#include "bots.h"
void cBotSimple::ChooseNextGridPosition()
{
	// Get our position
	int ourX = PositionX();
	int ourY = PositionY();

	int playerX = gTarget.PositionX();
	int playerY = gTarget.PositionY();

	int targetX = ourX;
	int targetY = ourY;
	if (ourX < playerX)
		targetX++;
	else if (ourX > playerX)
		targetX--;
	else if (ourY < playerY)
		targetY++;
	else if (ourY > playerY)
		targetY--;
	else {
		// we win?
	}
	SetNext(targetX, targetY, gLevel);
}