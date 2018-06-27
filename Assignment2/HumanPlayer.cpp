/*
Author: Alexis Varsava <av11sl@brocku.ca>
Date Created: October 20, 2017
Last Modified: November 9, 2017
*/

#include <iostream>
#include "HumanPlayer.h"

HumanPlayer::HumanPlayer(PLAYER_ID id)
{
	pid = id;
}

int HumanPlayer::getMove()
{
	char selection;
	int colVal;
	std::cout << "Please enter column: ";
	std::cin >> selection;
	std::cout << '\n';

	//A = 65, Z = 90
	if (selection >= 'A' && selection <= 'Z') {
		colVal = selection - 'A';
	}
	//a = 97, z = 122
	else if (selection >= 'a' && selection <= 'z') {
		colVal = selection - 'a';
	}
	else {
		colVal = 5555;
	}
	
	return colVal;
}

PLAYER_ID HumanPlayer::getId()
{
	return pid;
}

void HumanPlayer::resumeProcessing()
{
	return;
}