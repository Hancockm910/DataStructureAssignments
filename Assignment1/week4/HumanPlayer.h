#pragma once
#include "Player.h"
class HumanPlayer : public Player
{
private: 
	int row, col;
public:
	HumanPlayer(int row, int col);
	~HumanPlayer();
	void getBoard(Board board, int playerNum);
	void getMove(Board board, int &y, int &x);
	vector<NeighbourCell>captureSelect(vector<vector<NeighbourCell>>checkNeighbour);
};