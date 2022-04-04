#include "bots.h"
#include <cmath>
#include <stdlib.h>
using namespace std;

cBotSimple2::cBotSimple2()
{
	CalculateMoveDir();
}
void cBotSimple2::ChooseNextGridPosition()
{
	CalculateMoveDir();
	if (correctPosition) return;

	int idealX = PositionX() + cos(moveDir * (M_PI / 180));
	int idealY = PositionY() + sin(moveDir * (M_PI / 180));

	if (!IsDirectionBlacklisted(moveDir)) {
		if (!SetNext(idealX, idealY, gLevel)) {
			// Movement failed, blacklist this position and move on
			blacklistDir[arrayPos] = moveDir;
			arrayPos++;
		}
		else
			return; // Movement succeeded, no need for other logic
	}

	// Movement either failed this turn or was already blacklisted, either way we need to override its attempted direction
	if (IsDirectionBlacklisted(moveDir)) {
		bool validPos = false;
		// Check if our last blacklisted direction has been freed up
		float lastBlacklistedDir = blacklistDir[arrayPos - 1];
		int targetX = PositionX() + cos(lastBlacklistedDir * (M_PI / 180));
		int targetY = PositionY() + sin(lastBlacklistedDir * (M_PI / 180));
		validPos = SetNext(targetX, targetY, gLevel);
		// Great, this direction has been freed up so we can un-blacklist it
		if (validPos) {
			blacklistDir[arrayPos] = 1515; // nonsense data
			arrayPos--;
		}
		else {
			// Unfortunately this direction still doesn't work, use it as a base and loop until we find a freed up direction
			while (!validPos) {
				lastBlacklistedDir += 90;
				targetX = PositionX() + cos(lastBlacklistedDir * (M_PI / 180));
				targetY = PositionY() + sin(lastBlacklistedDir * (M_PI / 180));
				validPos = SetNext(targetX, targetY, gLevel);
				// We found another way we can't go! Blacklist it and move on
				if (!validPos) {
					blacklistDir[arrayPos] = lastBlacklistedDir;
					arrayPos++;
				}
			}
		}
	}
}

void cBotSimple2::CalculateMoveDir() {
	int ourX = PositionX();
	int ourY = PositionY();

	int playerX = gTarget.PositionX();
	int playerY = gTarget.PositionY();

	if (ourX < playerX) moveDir = 0;
	else if (ourX > playerX) moveDir = 180;
	else if (ourY < playerY) moveDir = 90;
	else if (ourY > playerY) moveDir = 270;

	if (ourX == playerX && ourY == playerY)
		correctPosition = true;
	else
		correctPosition = false;
	//else if (ourX != playerX || ourY != playerY)
	//{
	//	// We hit a wall, we can't move the direction we want but our other axis matches, but we need to move, just rotate 90
	//	moveDir += 90;
	//}
}

bool cBotSimple2::IsDirectionBlacklisted(float val)
{
	for (int i = 0; i < 4; i++) {
		if (blacklistDir[i] == val)
			return true;
	}
	return false;
}