/*
Author: Alexis Varsava <av11sl@brocku.ca>
Date Created: October 30, 2017
Last Modified: November 9, 2017
*/

#pragma once
#include "Player.h"
#include "Board.h"
#include <thread>

struct Node {
	int value;
	Board board;
	std::vector<Node*> children;
};

class AIPlayer : public Player {
public:
	AIPlayer(PLAYER_ID id, Board* cb);
	int getMove() override;
	PLAYER_ID getId() override;
	void resumeProcessing() override;

private:
	const int DEPTH = 4;
	Board* currentBoard;
	Node* currentTree;
	std::thread aiThread;
	static void buildTree(Node* currentNode, int depth, PLAYER_ID playerId);
	Node* trimTree();
	bool isTerminal(Node* node);
	int getBestMove(Node* tree, int depth, int a, int b, bool maximizingPlayer);
};