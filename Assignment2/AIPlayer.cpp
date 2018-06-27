/*
Author: Alexis Varsava <av11sl@brocku.ca>
Date Created: October 20, 2017
Last Modified: November 9, 2017
*/

#include <cstdlib>
#include <iostream>
#include <thread>
#include <algorithm>
#include "AIPlayer.h"


AIPlayer::AIPlayer(PLAYER_ID id, Board* cb)
{
	pid = id;
	currentBoard = cb;
	currentTree = new Node{ 0,
		*currentBoard, 
		std::vector<Node*>(currentBoard->getSize())};

	resumeProcessing();
}

int AIPlayer::getMove()
{
	aiThread.join();

	int ret;
	
	currentTree = trimTree();

	ret = getBestMove(currentTree,
		DEPTH,
		INT_MIN,
		INT_MAX,
		true);

	//ret = rand() % 8;

	return ret;
}

PLAYER_ID AIPlayer::getId()
{
	return pid;
}

void AIPlayer::resumeProcessing()
{
	aiThread = std::thread{ &AIPlayer::buildTree,
		currentTree,
		DEPTH,
		pid };
}

Node* AIPlayer::trimTree()
{
	for (auto child : currentTree->children) {
		if (child->board.matches(*currentBoard)) {
			return child;
		}
	}
}

//Uses alpha-beta pruning on trimmed tree to get the best move
// Based on: https://en.wikipedia.org/wiki/Alpha-beta_pruning#Pseudocode
int AIPlayer::getBestMove(Node* tree, int depth, int a, int b, bool maximizingPlayer)
{
	if (depth == 0 || isTerminal(tree)) {
		return tree->value;
	}

	if (maximizingPlayer) {
		int v = INT_MIN;
		for (auto child : tree->children) {
			v = std::max(v, getBestMove(child, depth - 1, a, b, false));
			a = std::max(a, v);
			if (b <= a) {
				break;
			}
		}
		return v;
	}
	else {
		int v = INT_MAX;
		for (auto child : tree->children) {
			v = std::min(v, getBestMove(child, depth - 1, a, b, true));
			b = std::min(b, v);
			if (b <= a) {
				break;
			}
		}
		return v;
	}
}

bool AIPlayer::isTerminal(Node* node)
{
	for (auto child : node->children) {
		if (child != nullptr) {
			return false;
		}
	}

	return true;
}

void AIPlayer::buildTree(Node* currentNode, int depth, PLAYER_ID playerId)
{
	//for every possible new board
	for (int i = 0; i != currentNode->children.size(); ++i) {
		//if at end of search
		if (depth == 0) {
			//ensure we have the current worth
			currentNode->value = currentNode->board.calculateWorth(playerId);

			//return
			return;
		}

		//copy the board we're considering
		Board newBoard = Board(currentNode->board);

		//get the opposite player ID
		PLAYER_ID newPid;
		if (playerId == ONE) {
			newPid = TWO;
		}
		else {
			newPid = ONE;
		}
		//if we can successfully add a checker to the column under 
		// consideration
		if (newBoard.addChecker(i, newPid)) {

			//create a new node 
			Node* newNode = new Node{
				newBoard.calculateWorth(newPid), 
				newBoard, 
				std::vector<Node*>(newBoard.getSize())};
			
			//add that to currentNode's children
			currentNode->children[i] = newNode;

			//recurse!!
			buildTree(
				currentNode->children[i],
				depth - 1,
				newPid);
		}
	}

	//After we've gone through all the children, return
	return;
}