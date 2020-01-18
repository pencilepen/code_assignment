#include<iostream>
#include <string>
using namespace std;

void compare(string sortArr[])
{
	int i = 0;
	string element;
	if (sortArr[i] < sortArr[i + 1])
	{
		element = sortArr[i];
		sortArr[i] = sortArr[i + 1];
		sortArr[i + 1] = element;
	}

}
int main()
{
	string sortArray[5] = { "a","f","g","q","t" };
	for (int q = 0; q < 5; q++)
	{
		cout << sortArray[q] << endl;
	}
	compare(sortArray);

}