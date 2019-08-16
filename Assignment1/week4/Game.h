#pragma once
#include<iostream>
#include <time.h>
using namespace std;
#include "Neighbour.h"
#include "board.h"
#include "Player.h"
#include "HumanPlayer.h"
#include "RandomPlayer.h"
#include "SmartPlayer.h"
#include "MonteCarlo.h"

class Game
{
private:
	int pOne = 0;
	int pTwo = 0;
public:
	Player* playerType[2];
	Game(int row, int col);
	void playGame(int row, int col);
	void playerSelection(int i, int ii, int row, int col);
	void playMultiple(int row, int col);
	~Game();

};

