/*
Author: Alexis Varsava <av11sl@brocku.ca>
Date Created: October 20, 2017
Last Modified: November 9, 2017
*/

#pragma once

#include <vector>
#include "Checker.h"

class Board {
private:
	int size;
	std::vector<std::vector<Checker*>> pieces;
	void resizeLines();
	void initLines();
	int getWrappedX(int x);

public:
	Board();
	Board(int customSize);
	Board(const Board &b);
	bool addChecker(int col, PLAYER_ID owner);
	bool isFullBottomLine();
	bool matches(Board b);
	int getSize();
	int calculateWorth(PLAYER_ID player);
	void printBoard();
	void dropLine();
	PLAYER_ID* getWinner();
	int getNumLines(PLAYER_ID owner, int length);
};