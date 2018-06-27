/*
Author: Alexis Varsava <av11sl@brocku.ca>
Date Created: October 20, 2017
Last Modified: October 25, 2017
*/

#pragma once

#include "PLAYER_ID.h"

class Checker {
private:
	PLAYER_ID pId;
public:
	Checker();
	Checker(PLAYER_ID owner);
	PLAYER_ID getOwner();
};