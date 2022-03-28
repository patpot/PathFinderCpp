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

	if (IsDirectionBlacklisted(moveDir) || !SetNext(idealX, idealY, gLevel)) {
		if (!IsDirectionBlacklisted(moveDir)) {
			blacklistDir[arrayPos] = moveDir;
			arrayPos++;
		}

		float overrideDir = moveDir;
		bool validPos = false;

		for (int i = arrayPos; i < 4; i++) {
			float moveAttemptDir = blacklistDir[i];
			int targetX = PositionX() + cos(moveAttemptDir * (M_PI / 180));
			int targetY = PositionY() + sin(moveAttemptDir * (M_PI / 180));
			validPos = SetNext(targetX, targetY, gLevel);
			if (validPos)
				blacklistDir[i] = 2562;
		}
		//while (!validPos) {
		//	overrideDir += 90;
		//	//if (IsDirectionBlacklisted(overrideDir) && overrideDir != blacklistDir[arrayPos-1])
		//	//	continue;

		//	int targetX = PositionX() + cos(overrideDir * (M_PI / 180));
		//	int targetY = PositionY() + sin(overrideDir * (M_PI / 180));
		//	validPos = SetNext(targetX, targetY, gLevel);

		//	if (!validPos && !IsDirectionBlacklisted(overrideDir)) {
		//		blacklistDir[arrayPos] = overrideDir;
		//		arrayPos++;
		//	}
		//}

		//if (IsDirectionBlacklisted(overrideDir))
		//{
		//	blacklistDir[arrayPos] = 26434;
		//	arrayPos--;
		//}
	}
	else if (gLevel.isValid(idealX, idealY) && IsDirectionBlacklisted(moveDir))
	{
		for (int i = 0; i < 4; i++) 
			blacklistDir[i] = 1313;

		arrayPos = 0;
	}
}

void cBotSimple2::CalculateMoveDir() {
	int ourX = PositionX();
	int ourY = PositionY();

	int playerX = gTarget.PositionX();
	int playerY = gTarget.PositionY();

	if		(ourX < playerX) moveDir = 0;
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