#include<iostream>

using namespace std;

int factorial(int);

int main() {
	cout << "Input an integer"<<endl;
	int n;
	cin >> n;
	if(n<0) 
		cout << "Error!";
	else {
	   int result = factorial(n);
       cout << "The factorial of n is "<< result << endl;
	}
    return 0;
}

int factorial(int n) {
   int result = 1; 
   if(n==0)
	   result = 1;
   else 
       for(int i=1;i<=n;i++)
		   result *= i;
	   
   return result;
}
