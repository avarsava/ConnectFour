/*
Author: Alexis Varsava <av11sl@brocku.ca>
Date Created: October 20, 2017
Last Modified: November 9, 2017
*/

#include <iostream>
#include <string>
#include "Board.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"

Player *p1, *p2, *currentPlayer;
Board currentBoard;

void initPlayers()
{
	bool needInput = true;
	int numHumans;
	do {
		std::cout << "Please enter the number of human players (0, 1, 2): ";
		std::cin >> numHumans;
		std::cout << '\n';
		if (numHumans < 0 || numHumans > 2) {
			std::cout << "Please enter a valid number.\n";
		}
		else {
			needInput = false;
		}
	} while (needInput);

	switch (numHumans) {
	case 0:
		p1 = new AIPlayer(ONE, &currentBoard);
		p2 = new AIPlayer(TWO, &currentBoard);
		break;
	case 1:
		p1 = new HumanPlayer(ONE);
		p2 = new AIPlayer(TWO, &currentBoard);
		break;
	case 2:
		p1 = new HumanPlayer(ONE);
		p2 = new HumanPlayer(TWO);
		break;
	}
	
}

void switchPlayer()
{
	if (currentPlayer == p1) {
		currentPlayer = p2;
	}
	else {
		currentPlayer = p1;
	}
}

PLAYER_ID* run()
{
	PLAYER_ID* winner;
	bool successfulMove, running = true;
	currentPlayer = p1;
	do{
		//TODO: invalid input checking
		successfulMove = currentBoard.addChecker(
			currentPlayer->getMove(), 
			currentPlayer->getId());
		currentPlayer->resumeProcessing();

		if (!successfulMove) {
			std::cout << "Invalid move, please try again. \n";
			continue;
		}
		else {
			if (currentPlayer == p1) {
				currentBoard.printBoard();
			}
			switchPlayer();
		}

		if (winner = currentBoard.getWinner()) {
			return winner;
		}

		if (currentBoard.isFullBottomLine()) {
			currentBoard.dropLine();
		}
	} while (running);
}

std::string printPlayerId(PLAYER_ID* pid)
{
	if (pid == nullptr) return "NULL";

	switch (*pid) {
	case ONE: return "ONE"; break;
	case TWO: return "TWO"; break;
	default: return "???"; break;
	}
}

void declareWinner(PLAYER_ID w)
{
	std::cout << "Congratulations, Player " << printPlayerId(&w) << "!!\n";
	std::cout << "Winning board: \n";
	currentBoard.printBoard();
}

int main()
{
	PLAYER_ID* winner;
	currentBoard = Board(8);

	initPlayers();

	declareWinner(*run());

	system("pause");
	return 0;
}