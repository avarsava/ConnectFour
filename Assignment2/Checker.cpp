/*
Author: Alexis Varsava <av11sl@brocku.ca>
Date Created: October 20, 2017
Last Modified: October 25, 2017
*/

#include "Checker.h"
#include "PLAYER_ID.h"

Checker::Checker(PLAYER_ID owner)
{
	pId = owner;
}

PLAYER_ID Checker::getOwner()
{
	return pId;
}