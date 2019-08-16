#ifndef BOARD_H_
#define BOARD_H_

#include<iostream>
#include<list>
#include<stack>
#include<vector>
#include"Neighbour.h"
#include<queue>
#include <unordered_map>
using namespace std;

class Board {
private:
	int row, col;
	list<int> left;
	int player = 1;
	vector<int>findEmpty;
	int playerOne, playerTwo;

public:
	int **grid; 
	int getRow();
	int getCol();
	Board(int r, int c) {
		row = r;
		col = c;
		grid = new int*[row];
		for (int i = 0; i < row; i++)
			grid[i] = new int[col];

		for (int i = 0; i < row; i++)
			for (int j = 0; j < col; j++)
				grid[i][j] = 0;

		for (int i = 0; i < row*col; i++) {
			left.push_back(i);
		}
		for (int i = 0; i < row*col; i++)
		{
			findEmpty.push_back(i);
		}
		static int count = 0;
	}
	~Board() {
		for (int i = 0; i < row; i++)
			delete[] grid[i];

		delete[] grid;
	}
	Board(Board& cboard) {
		row = cboard.row;
		col = cboard.col;

		grid = new int*[row];
		for (int i = 0; i < row; i++)
			grid[i] = new int[col];

		for (int i = 0; i < row; i++)
			for (int j = 0; j < col; j++)
				grid[i][j] = cboard.grid[i][j];
	}
	unordered_map<string, int> mapUnused(int y, int x);
	void addMove(vector<NeighbourCell>captureSelection, int player, int x, int y);
	void play(int & y, int & x);
	bool validateMove(int y, int x);
	vector<NeighbourCell>checkNeighbors(int, int);
	void sort(vector<vector<NeighbourCell>>&combinations, vector<NeighbourCell>&captureOptions, vector<NeighbourCell>&combine, int offset, int n);
	int captureNeighbours(vector<NeighbourCell>captureCheck, int y, int x);
	void printBoard();
	bool full();
	stack<pair<int, int>>record;
	int checkWinner();
	void declareWinner();
	vector<vector<NeighbourCell>>getVector(int y, int x);
	void clearLarge(vector<vector<NeighbourCell>>& v);
	void printCaptures(vector<vector<NeighbourCell>>captures, vector<NeighbourCell>neighbours);
};

#endif /* BOARD_H_ */