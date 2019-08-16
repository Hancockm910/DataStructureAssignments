/*********** Declaration*******
I hereby certify that no part of this assignment has been copied from
any other student’s work or from any other source. No part of the code
has been written/produced for me by another person or copied from any
other source.
I hold a copy of this assignment that I can produce if the original is
lost or damaged.
**************************/
#include "Game.h"
int main()
{
	srand(time(NULL));

	int row, col, pOne, pTwo;
	cout << "Input the size of board, say (3 3), (3 5) or (5 5): " << endl;
	row = 0;
	col = 0;
	cin >> row >> col;

	cout << "Select the first player's type: " << endl
		<< "Enter 1 for Human Player." << endl
		<< "Enter 2 for random inputs." << endl
		<< "Enter 3 for Minmax Player." << endl
		<< "Enter 4 for Monte Carlo player." << endl;

	cin >> pOne;
	cout << "Select the second player's type: " << endl
		<< "Enter 1 for Human Player." << endl
		<< "Enter 2 for random inputs." << endl
		<< "Enter 3 for Minmax Player." << endl
		<< "Enter 4 for Monte Carlo player." << endl;
	cin >> pTwo;

	Game gg(row, col);

	gg.playerSelection(pOne, pTwo, row, col);
	gg.playMultiple(row, col);	

	system("pause");
	return 0;
}