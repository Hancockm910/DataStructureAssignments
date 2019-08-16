#pragma once

#ifndef MONTECARLOPLAYER_H_
#define MONTECARLOPLAYER_H_
#include "Player.h"
#include<chrono>
#include <ctime>
const int simulation_times = 20;

class MonteCarloPlayer : public Player{
private:
	int row, col, playerNum;
	vector<int>emptySlots(Board board);
public:
	MonteCarloPlayer(int row, int col)
	:Player(row, col){
		this->row = row;
		this->col = col;
	}
	void getBoard(Board board, int playerNum) {
		this->playerNum = playerNum;
	}
	void getMove(Board board, int& y, int& x);
	double simulation(Board board);
	int expansion(Board board);
	void randomise(int &y, int &x, Board board);
	vector<NeighbourCell>captureSelect(vector<vector<NeighbourCell>>checkNeighbour);
};
#endif /* MONTECARLOPLAYER_H_ */



