/*
Author: Alexis Varsava <av11sl@brocku.ca>
Date Created: October 26, 2017
Last Modified: November 9, 2017
*/


#pragma once

#include "PLAYER_ID.h"

class Player {
protected:
	PLAYER_ID pid;

public:
	virtual int getMove() = 0;
	virtual PLAYER_ID getId() = 0;
	virtual void resumeProcessing() = 0;
};