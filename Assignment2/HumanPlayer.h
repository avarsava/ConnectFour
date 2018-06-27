/*
Author: Alexis Varsava <av11sl@brocku.ca>
Date Created: October 26, 2017
Last Modified: November 9, 2017
*/

#pragma once
#include "Player.h"

class HumanPlayer : public Player {
public:
	HumanPlayer(PLAYER_ID id);
	int getMove() override;
	PLAYER_ID getId() override;
	void resumeProcessing() override;
};