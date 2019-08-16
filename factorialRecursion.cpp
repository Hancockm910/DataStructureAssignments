#include<iostream>

using namespace std;

int factorial(int);

int main() {
	cout << "Input an integer"<<endl;
	int n;
	cin >> n;
	if(n<0) 
		cout << "Error!";
	else 
       cout << "\nThe factorial of n is "<< factorial(n) << endl;

    return 0;
}

int factorial(int n) {
   int result = 1;
   if(n==0)
	   result = 1;
   else 
       result = n*factorial(n-1);

   return result;
}
