#include <iostream>
using namespace std;
/*int factorial(int);
int main()
{
	int num, factor = 1;

	cout << "Enter an integer.\n";
	cin >> num;
	//iterative 
	for (int i = 0; i < num; i++)
		factor = factorial(num);
	cout << num;

	system("pause");
	return 0;
}

int factorial(int n)
{
	//factorial solution
	if (n == 0)
		return 1;
	else
		return n*factorial(n - 1);

}
*/
int fib(int);
int main()
{
	int n, fnum=1;
	
	/*cout << "what\n";
	cin >> n;

	for (int i = 0; i < n; i++)
		fnum = fib(n);*/
	cout << fib(10) << endl;
	//cout << fnum << endl;
	system("pause");
	return 0;
}
int fib(int n)
{
	if (n == 0)
		return 0;
	else if (n == 1)
		return 1;
	else
		return fib(n-2) + fib(n - 1);
}