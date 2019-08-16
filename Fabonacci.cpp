/*	This program prints out a Fibonacci series.
*/
#include <iostream>
#include <iomanip>

using namespace std;

//	Prototype Statements 
long fib (long num);

int main (void) {
	int n;
	cout << "This program prints a Fibonacci series.\n";
	cout << "How many numbers do you want? ";
	cin  >> n;
	if (n < 2)
	    n = 2;

	cout << "\nFirst " << n 
	     << " Fibonacci numbers: \n";
	for (int i = 0; i < n; i++) {
	     if (i % 5 != 0)
	         cout << setw (8) << fib(i);
	     else
	         cout << endl << setw (8) << fib(i);
	    } // for
	cout << endl; 
	return 0;
}	//  main 


long fib (long n) {
	if (n == 0 || n == 1) // Base Case 
	    return n;
	else 
	    return (fib(n-1) + fib (n-2));
}	// fib 
