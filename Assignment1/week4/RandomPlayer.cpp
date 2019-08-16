#include "RandomPlayer.h"
#include "RandomPlayer.h"

RandomPlayer::RandomPlayer(int row, int col)
	:Player(row, col)
{
	this->row = row;
	this->col = col;
}

//RandomPlayer::RandomPlayer(int row, int col)
//{
//}

RandomPlayer::~RandomPlayer()
{
};

void RandomPlayer::scanEmpty()
{
	int selection;
	selection = rand() % emptySpots.size();
}

void RandomPlayer::getMove(Board board, int &y, int &x)
{
	getBoard(board, 0);
	int selection = rand() % this->emptySpots.size();
	x = emptySpots[selection] % col;
	y = emptySpots[selection] / col;
	emptySpots.clear();
}

void RandomPlayer::getBoard(Board board, int playerNum)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (board.grid[i][j] == 0)
			{
				emptySpots.push_back(i*col+j);
			}
		}
	}
}

vector<NeighbourCell> RandomPlayer::captureSelect(vector<vector<NeighbourCell>> checkNeighbour)
{
	vector<NeighbourCell>captureSelect;
	if (!checkNeighbour.empty())
		captureSelect = checkNeighbour[rand() % checkNeighbour.size()];
	else
		cout << "No capture options available" << endl;
	return captureSelect;
}