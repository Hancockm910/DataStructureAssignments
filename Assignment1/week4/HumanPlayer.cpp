#include "HumanPlayer.h"

HumanPlayer::HumanPlayer(int row, int col)
	:Player(row, col)
{
	this->row = row;
	this->col = col;
}

HumanPlayer::~HumanPlayer()
{
}
void HumanPlayer::getBoard(Board board, int playerNum)
{
}
void HumanPlayer::getMove(Board board, int & y, int & x)
{
	cout << "Player " << symbol << " enter your coord: " << endl;
	cin >> x >> y;
	x--;
	y--;
}

vector<NeighbourCell> HumanPlayer::captureSelect(vector<vector<NeighbourCell>> checkNeighbour)
{
	vector<NeighbourCell>returnedVector;
	if (checkNeighbour.size() == 1)
	{
		for (int i = 0; i < checkNeighbour[0].size(); i++)
			returnedVector.push_back(checkNeighbour[0][i]);
		return returnedVector;
	}

	if (!checkNeighbour.empty())
	{
		cout << "Select an option \n";
		int option;
		cin >> option;
		cout << "You have selected: " << endl;

		for (int i = 0; i < checkNeighbour[option - 1].size(); i++)
			returnedVector.push_back(checkNeighbour[option - 1][i]);
		for (int i = 0; i < returnedVector.size(); i++)
			cout << returnedVector[i].first << returnedVector[i].pipCount << endl;;
	}
	else
		cout << "No capture options available.\n";

	return returnedVector;
}