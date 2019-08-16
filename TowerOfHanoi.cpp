#include <iostream>

using namespace std;

void moveDisks(int n, char A, char C, char B)
{
	if(n>1) {
        moveDisks(n-1, A, B, C);//general case
        moveDisks(1, A, C, B); //base case
        moveDisks(n-1, B, C, A);//general case
	} else {// base case code n=1
		 cout << "Move disk " << n << " from " << A
		         << " to " << C << "." << endl;
	}

}

int main()
{
    int n = 3;
    moveDisks(n, 'A', 'C', 'B');
    return 0;
}


