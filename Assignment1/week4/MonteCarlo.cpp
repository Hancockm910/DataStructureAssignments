#include "MonteCarlo.h"

vector<NeighbourCell> MonteCarloPlayer::captureSelect(vector<vector<NeighbourCell>> checkNeighbour)
{
	vector<NeighbourCell>retVec;
	if (checkNeighbour.size() == 1)
	{
		for (int i = 0; i < checkNeighbour[0].size(); i++)
			retVec.push_back(checkNeighbour[0][i]);
		return retVec;
	}
	if (!checkNeighbour.empty())
	{
		int totalPip = 0;
		int totalOpponents = 0;

		for (int oppOwned = 0; oppOwned < 5; oppOwned++)
		{
			for (int i = checkNeighbour.size() - 1; i >= 0; i--)
			{
				totalPip = 0;
				totalOpponents = 0;
				for (int k = checkNeighbour[i].size() - 1; k >= 0; k--)
				{
					if (playerNum == 0 && checkNeighbour[i][k].pipCount > 0)
						totalOpponents++;
					else if (playerNum == 1 && checkNeighbour[i][k].pipCount < 0)
						totalOpponents++;

					totalPip = abs(checkNeighbour[i][k].pipCount);
				}
				if (totalOpponents == checkNeighbour[i].size() - oppOwned && totalPip == 6)
				{
					retVec = checkNeighbour[i];
					return retVec;
				}
			}
		}
		for (int oppOwned = 0; oppOwned < 5; oppOwned++)
		{
			for (int i = checkNeighbour.size() - 1; i >= 0; i--)
			{
				totalOpponents = 0;
				for (int k = checkNeighbour[i].size() - 1; k >= 0; k--)
				{
					if (playerNum == 0 && checkNeighbour[i][k].pipCount > 0)
						totalOpponents++;
					else if (playerNum == 1 && checkNeighbour[i][k].pipCount < 0)
						totalOpponents++;
				}
				if (totalOpponents == checkNeighbour[i].size() - oppOwned)
				{
					retVec = checkNeighbour[i];
					return retVec;
				}
			}
		}
	}
	return retVec;
}

vector<int> MonteCarloPlayer::emptySlots(Board board)
{
	vector<int>emptySpaces;
	for (int x = 0; x < row; x++)
		for (int y = 0; y < col; y++)
			if (board.grid[x][y] == 0)
				emptySpaces.push_back(x*col + y);
	
	return emptySpaces;
}

void MonteCarloPlayer::getMove(Board board, int & y, int & x)
{

	vector<int> emptyCells = emptySlots(board);
	if (emptyCells.empty())
		return;
	if (emptyCells.size() == 1)
	{
		x = emptyCells[0] % col;
		y = emptyCells[0] / col;
		return;
	}
	priority_queue<Cells> moves;

	for (int index : emptyCells) 
	{
		//////////////////////////////
		auto start = std::chrono::system_clock::now();
		///////////////////////////////
		int yPos = index / col;
		int xPos = index % col;
		Board tempBoard(board);
		tempBoard.addMove(captureSelect(tempBoard.getVector(yPos, xPos)), playerNum, yPos, xPos);
		//tempBoard.printBoard();
		if (tempBoard.full()) {
			if (tempBoard.checkWinner() == playerNum) {
				x = xPos;
				y = yPos;
				return;
			}
			else
				continue;
		}

		double utility = simulation(tempBoard);

		Cells c;
		c.xLoc = xPos;
		c.yLoc = yPos;
		c.heuristic = utility;
		moves.push(c);
		///////////////////////////
		auto end = chrono::system_clock::now();

		chrono::duration<double> elapsed_seconds = end - start;
		time_t end_time = chrono::system_clock::to_time_t(end);

		cout << "Finished computation. Elapsed time: " << elapsed_seconds.count() << "s\n";
		////////////////////////////
	}

	if (moves.size() > 0) {
		x = moves.top().xLoc;
		y = moves.top().yLoc;

		cout << moves.size() << " Monte Carlo Utility = " << moves.top().heuristic << " at ("
			<< x << "," << y << ")" << endl;
	}
}

double MonteCarloPlayer::simulation(Board board)
{

	int winning = 0;

	for (int i = 0; i < simulation_times; i++) {
		Board tempBoard(board);
		winning += expansion(tempBoard);
	}

	return ((double)winning / (double)simulation_times);
}

int MonteCarloPlayer::expansion(Board board)
{
	if (board.full()) {
		if (board.checkWinner() == playerNum % 2)
			return  1;
		else
			return -1;
	}

	int x, y;
	randomise(y, x, board);
	board.addMove(captureSelect(board.getVector(y, x)), playerNum % 2, y, x);
	playerNum++;
	return expansion(board);
}

void MonteCarloPlayer::randomise(int & y, int & x, Board board)
{
	vector<int>available = emptySlots(board);

	int i = rand() % available.size();
	y = available[i] / col;
	x = available[i] % col;
}
