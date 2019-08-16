#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS

#include "SmartPlayer.h"
#include<chrono>
#include <ctime>

SmartPlayer::SmartPlayer(int row, int col)
	:Player(row, col)
{
	this->row = row;
	this->col = col;
}

vector<int> SmartPlayer::emptySlots(Board board)
{
	vector<int>emptySpaces;
	for (int x = 0; x < row; x++)
		for (int y = 0; y < col; y++)
			if (board.grid[x][y] == 0)
				emptySpaces.push_back(x*col + y);
	return emptySpaces;
}

SmartPlayer::~SmartPlayer()
{
}

void SmartPlayer::getMove(Board board, int & y, int & x)
{
	vector<int>moveChoices = emptySlots(board);
	random_shuffle(moveChoices.begin(), moveChoices.end());

	priority_queue<Cells>moveOutcome;

	for (int i : moveChoices)
	{
		//////////////////////////////
		auto start = std::chrono::system_clock::now();
		///////////////////////////////
		steps = 1000;
		int xPos = i % col;
		int yPos = i / col;
		Board tempBoard(board);
		tempBoard.addMove(captureSelect(tempBoard.getVector(yPos, xPos)), playerNum, yPos, xPos);
		//tempBoard.printBoard();

		if (tempBoard.full())
		{
			if (tempBoard.checkWinner() == playerNum)
			{
				x = xPos;
				y = yPos;
				return;
			}
		}
		double minUtility = miniMove(tempBoard);
		
		OppSix = false;

		Cells cell;
		cell.xLoc = xPos;
		cell.yLoc = yPos;
		cell.heuristic = minUtility;
		moveOutcome.push(cell);

		if (moveOutcome.size() > 0) 
		{
			x = moveOutcome.top().xLoc;
			y = moveOutcome.top().yLoc;

			cout << moveOutcome.size() << " MiniMax Utility = " << moveOutcome.top().heuristic
				<< " at (" << (x + 1) << "," << (y + 1) << ")" << endl;
		}
		///////////////////////////
		auto end = chrono::system_clock::now();
		chrono::duration<double> elapsed_seconds = end - start;
		time_t end_time = chrono::system_clock::to_time_t(end);
		cout << "Finished computation. Elapsed time: " << elapsed_seconds.count() << "s\n";
		////////////////////////////
	}
}

void SmartPlayer::getBoard(Board board, int playerNum)
{
	this->playerNum = playerNum;
}

vector<NeighbourCell> SmartPlayer::captureSelect(vector<vector<NeighbourCell>>checkNeighbour)
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

vector<NeighbourCell> SmartPlayer::enemyCapture(vector<vector<NeighbourCell>>checkNeighbour)
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
					OppSix = true;
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

double SmartPlayer::totalSixes(Board board)
{
	double hitSix = 0.0;
	for (int x = 0; x < row; x++)
		for (int y = 0; y < col; y++)
		{
			if (playerNum == 0 && board.grid[x][y] == 6)
				hitSix += 0.01;
			else if (playerNum == 1 && board.grid[x][y] == -6)
				hitSix += 0.01;
		}
	return hitSix;
}


double SmartPlayer::maxMove(Board board)
{
	vector<int>emptySquares = emptySlots(board);
	if (OppSix)
	{
		OppSix = false;
		return -0.1;
	}
	if (emptySquares.empty() || steps <= 0)
	{
		if (totalSixes(board) > 0.01)
			return totalSixes(board);

		return 0.01;
	}		

	random_shuffle(emptySquares.begin(), emptySquares.end());
	double maxUtility = -2;
	for (int index : emptySquares) 
	{
		int y = index / col;
		int x = index % col;
		Board tempBoard(board);
		tempBoard.addMove(captureSelect(tempBoard.getVector(y, x)), playerNum, y, x);
		//tempBoard.printBoard();

		if (tempBoard.full()) 
		{
			int gameOver = tempBoard.checkWinner();
			if (gameOver == playerNum)
				return 1; 
			else
				return -1; 
		}
		double utility;
		utility = miniMove(tempBoard);

		if (utility > maxUtility) 
			maxUtility = utility;
	}
	steps--;
	return maxUtility;
}

double SmartPlayer::miniMove(Board board)
{
	vector<int> emptyCells = emptySlots(board);
	if (OppSix)
	{
		OppSix = false;
		return -0.05;
	}

	if (emptyCells.empty() || steps <= 0)
		return -0.01;
	int altPlayer;
	if (playerNum == 0)
		altPlayer = 1;
	else
		altPlayer = 0;
	random_shuffle(emptyCells.begin(), emptyCells.end());
	double minUtility = 2;
	for (int index : emptyCells) 
	{
		int y = index / col;
		int x = index % col;
		Board tempBoard(board);
		tempBoard.addMove(enemyCapture(tempBoard.getVector(y, x)), altPlayer, y, x);
		//tempBoard.printBoard();

		if (tempBoard.full()) 
		{
			if (tempBoard.checkWinner() == playerNum)
				return 1; 
			else
				return -1; 
		}

		double utility = maxMove(tempBoard);

		if (utility < minUtility) 
			minUtility = utility;
	}
	steps--;
	return minUtility;
}