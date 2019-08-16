#pragma once
#include "Player.h"
class RandomPlayer : public Player
{
public:
	RandomPlayer(int row, int col);
	~RandomPlayer();
	void scanEmpty();
	vector<int>emptySpots;
	void getMove(Board board, int & y, int & x);
	int row;
	int col;
	void getBoard(Board board, int playerNum);
	vector<NeighbourCell>captureSelect(vector<vector<NeighbourCell>>checkNeighbour);
};