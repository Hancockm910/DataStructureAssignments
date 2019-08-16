#pragma once
#include"Player.h"

class SmartPlayer: public Player
{
private:
	int row, col, steps;
	vector<int>emptySlots(Board board);
	int playerNum;
	bool OppSix = false;
public:
	SmartPlayer(int row, int col);
	~SmartPlayer();
	void getMove(Board board, int& y, int& x);
	void getBoard(Board board, int playerNum);
	vector<NeighbourCell>captureSelect(vector<vector<NeighbourCell>>checkNeighbour);
	vector<NeighbourCell>enemyCapture(vector<vector<NeighbourCell>>checkNeighbour);
	double totalSixes(Board board);

	double miniMove(Board board);
	double maxMove(Board board);
};