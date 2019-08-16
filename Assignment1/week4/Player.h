#pragma once
#include "Board.h"

using namespace std;
class Player
{
public:
	Player(int row, int col);
	~Player();
	virtual void getMove(Board board, int& y, int& x) = 0;//stepping stone to sub class' getMove
	virtual void getBoard(Board board, int playerNum) = 0;
	virtual vector<NeighbourCell>captureSelect(vector<vector<NeighbourCell>>checkNeighbour) = 0;
	char setSymbol();
	char symbol;
private:
};