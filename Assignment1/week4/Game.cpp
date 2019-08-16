#include <chrono>
#include <ctime>
#include "Game.h"

Game::Game(int row, int col)
{
}

void Game::playGame(int row, int col)
{
	int x, y;
	int index = 0;
	Board board(row, col);

	board.printBoard();
	while (!board.full())
	{
		playerType[index % 2]->getBoard(board, index % 2);
		do
		{
			playerType[index % 2]->getMove(board, y, x);
		} while (board.validateMove(y, x));
		//board.printCaptures(board.getVector(y, x), board.checkNeighbors(y, x));
		board.addMove(playerType[index % 2]->captureSelect(board.getVector(y, x)), index % 2, y, x);
		index++;
		board.printBoard();
	}
	board.checkWinner();
	if (board.checkWinner() == 0)
		pOne++;
	else
		pTwo++;
	board.declareWinner();
	board.printBoard();
	//vector<pair<int,int>>reverseOrder;
	//while (!board.record.empty())
	//{
	//	reverseOrder.push_back(make_pair(board.record.top().first,board.record.top().second));
	//	board.record.pop();
	//}
	//for (int i = 0; i < reverseOrder.size(); i++)
	//{
	//	cout << "Move " << i + 1 << ": " << reverseOrder[i].first << " " << reverseOrder[i].second << endl;
	//}
}

void Game::playerSelection(int i, int ii, int row, int col)
{
	if (i == 1)
		playerType[0] = new HumanPlayer(row, col);
	else if (i == 2)
		playerType[0] = new RandomPlayer(row, col);
	else if (i == 3)
		playerType[0] = new SmartPlayer(row, col);
	else if (i == 4)
		playerType[0] = new MonteCarloPlayer(row, col);

	if (ii == 1)
		playerType[1] = new HumanPlayer(row, col);
	else if (ii == 2)
		playerType[1] = new RandomPlayer(row, col);
	else if (ii == 3)
		playerType[1] = new SmartPlayer(row, col);
	else if (ii == 4)
		playerType[1] = new MonteCarloPlayer(row, col);
}

void Game::playMultiple(int row, int col)
{
	int input;
	cout << "How many games?" << endl;
	cin >> input;

	for (int i = 0; i < input; i++)
	{		
		//////////////////////////////
		auto begin = std::chrono::system_clock::now();
		///////////////////////////////
		playGame(row, col);

		///////////////////////////
		auto finish = chrono::system_clock::now();

		chrono::duration<double> elapsed_seconds = finish - begin;
		time_t end_time = chrono::system_clock::to_time_t(finish);

		cout << "Finished game " << input << ". Elapsed time: " << elapsed_seconds.count() << "s\n";
		////////////////////////////
	}
	cout << "\n\nPlayer One wins: " << pOne;
	cout << "\n\nPlayer Two wins: " << pTwo << endl;		
}

Game::~Game()
{
}
