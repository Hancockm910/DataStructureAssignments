#include "board.h"
#include <unordered_map>

vector<NeighbourCell> Board::checkNeighbors(int y, int x) 
{

	vector<NeighbourCell>captureCheck;
	NeighbourCell check;
	int totalCount = 0;
	if ((y - 1 >= 0) && grid[y - 1][x] != 0 && grid[y - 1][x] <= 6)
	{
		check.first = "Up: ";
		check.pipCount = grid[y - 1][x];
		captureCheck.push_back(check);
	}
	if ((y + 1 < row) && grid[y + 1][x] != 0 && grid[y + 1][x] <= 6)
	{
		check.first = "Down: ";
		check.pipCount = grid[y + 1][x];
		captureCheck.push_back(check);
	}
	if ((x - 1 >= 0) && grid[y][x - 1] != 0 && grid[y][x - 1] <= 6)
	{
		check.first = "Left: ";
		check.pipCount = grid[y][x - 1];
		captureCheck.push_back(check);
	}
	if ((x + 1 < col) && grid[y][x + 1] != 0 && grid[y][x + 1] <=6)
	{
		check.first = "Right: ";
		check.pipCount = grid[y][x + 1];
		captureCheck.push_back(check);
	}
	for (int i = 0; i < captureCheck.size(); i++)
	{
		//cout << "Neighbours: ";
		//cout << captureCheck[i].first << captureCheck[i].pipCount << endl;
		totalCount += abs(captureCheck[i].pipCount);
	}
	//cout << "Total neighbour pipcount: " << totalCount << endl;
	return captureCheck;
}

void Board::sort(vector<vector<NeighbourCell>>&combinations, vector<NeighbourCell>&captureOptions, vector<NeighbourCell>&combine, int offset, int n)
{
	if (n == 0) 
	{
		combinations.push_back(combine);
		return;
	}
	for (int i = offset; i <= captureOptions.size() - n; ++i) 
	{
		combine.push_back(captureOptions[i]);
		sort(combinations, captureOptions, combine, i + 1, n - 1);
		combine.pop_back();
	}
}


int Board::captureNeighbours(vector<NeighbourCell>captureCheck, int y, int x)
{
	int total = 0;


	for (int i = 0; i < captureCheck.size(); i++)
	{
		total += abs(captureCheck[i].pipCount);

		if (captureCheck[i].first == "Up: ")
		{
			grid[y - 1][x] = 0;
		}
		if (captureCheck[i].first == "Down: ")
		{
			grid[y + 1][x] = 0;
		}
		if (captureCheck[i].first == "Left: ")
		{
			grid[y][x - 1] = 0;
		}
		if (captureCheck[i].first == "Right: ")
		{
			grid[y][x + 1] = 0;
		}
	}
	return total;
}

bool Board::validateMove(int y, int x)
{
	return (y < 0 || y > row 
		|| x < 0 || x > col 
		|| grid[y][x] != 0);
}

int Board::getRow()
{
	return row;
}

int Board::getCol()
{
	return col;
}



void Board::addMove(vector<NeighbourCell>captureSelection, int player, int y, int x)
{
	int total = captureNeighbours(captureSelection, y, x);
	if (player == 0)
	{
		if (total == 0)
			grid[y][x] = 1;
		else
			grid[y][x] = total;
	}
	else
	{
		if (total == 0)
			grid[y][x] = -1;
		else
		{
			total = -total;
			grid[y][x] = total;
		}

	}
}

void Board::play(int &y, int &x) 
{
	record.push(make_pair(x, y));
}

void Board::printBoard() {
	cout << "    ";
	for (int j = 0; j < col; j++) 
	{
		cout << j + 1 << "   ";
	}
	cout << endl;

	for (int i = 0; i < row; i++) 
	{
		cout << "  ";
		for (int j = 0; j < col; j++) 
		{
			cout << " ---";
		}
		cout << endl;

		cout << (i + 1) << " |";

		for (int j = 0; j < col; j++) 
		{
			if (grid[i][j] == 0) 
			{
				cout << "   |";
			}
			else if (grid[i][j] > 0) 
			{
				cout << " " << grid[i][j] << " |";
			}
			else if (grid[i][j] < 0) {
				cout << "" << grid[i][j] << " |";
			}
		}
		cout << endl;
	}
	cout << "  ";

	for (int j = 0; j < col; j++) 
	{
		cout << " ---";
	}
	cout << endl << endl;
}
bool Board::full()
{
	for (int x = 0; x < row; x++)
		for (int y = 0; y < col; y++)
			if (grid[x][y] == 0)
				return false;
	return true;
}

int Board::checkWinner()
{
	playerOne = 0;
	playerTwo = 0;
	for (int x = 0; x < col; x++)
	{
		for (int y = 0; y < row; y++)
		{
			if (grid[y][x] > 0)
				playerOne++;
			else
				playerTwo++;
		}
	}
	if (playerOne > playerTwo)
		return 0;
	else 
		return 1;
}

void Board::declareWinner()
{
	cout << "\n\nPlayer One square count: " << playerOne << endl;
	cout << "Player Two square count: " << playerTwo << endl;
	if (checkWinner() == 0)
	{
		cout << "Winner: Player One!!!!\n\n" << endl;
	}
	else
	{
		cout << "Winner: Player Two!!!!\n\n" << endl;
	}
}

vector<vector<NeighbourCell>> Board::getVector(int y, int x)
{
	vector<NeighbourCell>captureOptions = checkNeighbors(y, x);
	vector<vector<NeighbourCell>>combinations;
	vector<NeighbourCell>combine;

	for (int i = 2; i <= captureOptions.size(); i++)
	{
		sort(combinations, captureOptions, combine, 0, i);
	}
	clearLarge(combinations);
	int count = 0;
	int sum = 0;
	for (int i = 0; i < combinations.size(); i++)
	{
		count++;
		sum = 0;
		//cout << "Combination " << count << " [";
		for (int k = 0; k < combinations[i].size(); k++)
		{
			//cout << combinations[i][k].first << combinations[i][k].pipCount << " ";
			sum += abs(combinations[i][k].pipCount);
		}
		//cout << "] \n" << "\t     Total: " << sum << endl;
	}
	return combinations;
}

void Board::clearLarge(vector<vector<NeighbourCell>>& v)
{
	int sum = 0;
	for (int i = 0; i < v.size(); i++)
	{
		sum = 0;
		for (int k = 0; k < v[i].size(); k++)
			sum += abs(v[i][k].pipCount);
		if (sum > 6)
		{
			v.erase(v.begin() + i);
			clearLarge(v);
		}
	}
}

void Board::printCaptures(vector<vector<NeighbourCell>> captures, vector<NeighbourCell> neighbours)
{
	int sum = 0;

	for (int i = 0; i < neighbours.size(); i++)
	{
		cout << "Neighbours: ";
		cout << neighbours[i].first << neighbours[i].pipCount << endl;
		sum += abs(neighbours[i].pipCount);
	}
	cout << "Total neighbour pipcount: " << sum << endl;

	int count = 0;
	for (int i = 0; i < captures.size(); i++)
	{
		count++;
		sum = 0;
		cout << "Combination " << count << " [";
		for (int k = 0; k < captures[i].size(); k++)
		{
			cout << captures[i][k].first << captures[i][k].pipCount << " ";
			sum += abs(captures[i][k].pipCount);
		}
		cout << "] \n" << "\t     Total: " << sum << endl;
	}
}

unordered_map<string, int> Board::mapUnused(int y, int x)
{
	unordered_map<string, int> neighbourSquares;
	if ((y - 1 >= 0) && grid[y - 1][x] != 0)
		neighbourSquares["Up"] = grid[y - 1][x];
	if ((y + 1 < row) && grid[y + 1][x] != 0)
		neighbourSquares["Down"] = grid[y + 1][x];
	if ((x - 1 >= 0) && grid[y][x - 1] != 0)
		neighbourSquares["Left"] = grid[y][x - 1];
	if ((x + 1 < col) && grid[y][x + 1] != 0)
		neighbourSquares["Right"] = grid[y][x + 1];

	return neighbourSquares;
}
