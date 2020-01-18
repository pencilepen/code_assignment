#include <iostream>
using namespace std;

void myFUnc(int* x)
{
	*x = 100;
}
int main()
{
	int var=20;

	myFUnc(&var);
	cout << var;

	
	system("pause");
	return 0;
}