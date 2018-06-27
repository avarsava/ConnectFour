/*
Author: Alexis Varsava <av11sl@brocku.ca>
Date Created: October 20, 2017
Last Modified: November 9, 2017
*/

#include <iostream>
#include "Checker.h"
#include "Board.h"
#include "PLAYER_ID.h"

const int DEFAULT_SIZE{ 8 };
const int ASCII_CAPITAL_A{ 65 };

typedef struct {
	int x, y;
} Direction;

Board::Board()
{
	size = DEFAULT_SIZE;
	resizeLines();
	initLines();
}

Board::Board(int customSize)
{
	size = customSize;
	resizeLines();
	initLines();
}

Board::Board(const Board &b)
{
	size = b.size;
	resizeLines();
	for (int i = 0; i != size; ++i) {
		for (int j = 0; j != size; ++j) {
			pieces[i][j] = b.pieces[i][j];
		}
	}
}

int Board::getSize()
{
	return size;
}

void Board::resizeLines()
{
	pieces.resize(size);
	for (auto& line : pieces) {
		line.resize(size);
	}
}

void Board::initLines()
{
	for (auto& line : pieces) {
		for (auto& piece : line) {
			piece = nullptr;
		}
	}
}

void Board::printBoard()
{
	char symbol;
	for (auto line : pieces) {
		for (auto piece : line) {
			if (piece) {
				symbol = piece->getOwner();
			}
			else {
				symbol = ' ';
			} 
			std::cout << symbol << ' ';
		}
		std::cout << "\n";
	}
	for (int i = 0; i != size; ++i) {
		std::cout << char(ASCII_CAPITAL_A + i) << ' ';
	}
	std::cout << '\n';
}

void Board::dropLine()
{
	std::vector<std::vector<Checker*>> newPieces;
	newPieces.resize(size);

	for (int i = size - 1; i != 0; --i) {
		newPieces[i] = pieces[i - 1];
	}
	newPieces[0] = std::vector<Checker*>();
	newPieces[0].resize(size);
	pieces = newPieces;
}

bool Board::addChecker(int col, PLAYER_ID owner)
{
	for (int i = size - 1; i != 0; --i) {
		if (pieces[i][col] == nullptr) {
			pieces[i][col] = new Checker(owner);
			return true;
		}
	}
	return false;
}

int Board::calculateWorth(PLAYER_ID player)
{
	int score{ 0 };
	int lengths[]{ 2,3,4 };
	PLAYER_ID opponent;
	if (player == ONE) {
		opponent = TWO;
	}
	else {
		opponent = ONE;
	}

	for (auto length : lengths) {
		score += length * getNumLines(player, length);
		score -= length * getNumLines(opponent, length);
	}
	return score;
}

bool Board::isFullBottomLine()
{
	for (auto col : pieces[size - 1]) {
		if (col == nullptr) {
			return false;
		}
	}
	return true;
}


PLAYER_ID* Board::getWinner()
{
	PLAYER_ID* winner = nullptr;

	for (PLAYER_ID player : {ONE, TWO}) {
		if (getNumLines(player, 4) >= 1) {
			winner = &player;
			break;
		}
	}

	return winner;
}

int Board::getNumLines(PLAYER_ID owner, int length)
{
	Direction directions[4] = {
		Direction{ 1, 0 }, //Search vertically
		Direction{ 0, 1 },//Search horizontally
		Direction{ 1, 1 }, //Search right diagonal
		Direction{ 1, -1 }  //Search left diagonal
	};

	int count{ 0 };

	for (int i = 0; i != size; ++i) { //iterate over rows
		for (int j = 0; j != size; ++j) { //iterate over spaces within row
			if (pieces[i][j] != nullptr) { //skip if no line could start here
				//make sure we're looking at owner's line
				if(pieces[i][j]->getOwner() != owner) continue;

				//search through all the possible lines
				for (Direction d : directions) {
					//if searching through columns would take us off the board,
					// skip the search.
					if (d.y > 0 && i > size - 4) continue;
					if (d.y < 0 && i < 3) continue;

					//get all the spots in the line where pieces could be
					Checker* piece4 = pieces[i + d.y + d.y + d.y][getWrappedX(j + d.x + d.x + d.x)];
					Checker* piece3 = pieces[i + d.y + d.y][getWrappedX(j + d.x + d.x)];
					Checker* piece2 = pieces[i + d.y][getWrappedX(j + d.x)];


					//if the pieces exist (and have a blank after them) 
					// and are all the same owner, a line is formed
					switch (length) {
					case 2:
						if (piece2 && piece2->getOwner() == owner
							&& !piece3) {
							count++;
						}
						break;
					case 3:
						if (piece2 && piece2->getOwner() == owner
							&& piece3 && piece3->getOwner() == owner
							&& !piece4) {
							count++;
						}
						break;
					case 4:
						if (piece2 && piece2->getOwner() == owner
							&& piece3 && piece3->getOwner() == owner
							&& piece4 && piece4->getOwner() == owner) {
							count++;
						}
						break;
					}
					
				}
			}

		}
	}

	return count;
}

//Enables line detection wrapping around the sides
int Board::getWrappedX(int x)
{
	//wrap around right side
	if (x >= size) {
		return x - size;
	}
	//wrap around left side
	else if (x < 0){
		return size + x;
	}
	//else return value
	return x;
}

bool Board::matches(Board b)
{
	for (int i = 0; i != size; ++i) {
		for (int j = 0; j != size; ++j) {

			//if both pieces are present
			if (pieces[i][j] != nullptr && b.pieces[i][j] != nullptr) {

				//if their owners do not match, boards do not match
				if (pieces[i][j]->getOwner() != b.pieces[i][j]->getOwner()) {
					return false;
				}
			}

			//or if both spots are blank
			else if (pieces[i][j] == nullptr && b.pieces[i][j] == nullptr) {
				continue;
			}

			//if there is a piece on one board and the piece isn't on the other,
			// boards do not match
			else {
				return false;
			}
		}
	}
	return true;
}