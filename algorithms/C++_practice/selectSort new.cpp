#include<iostream>
#include <string>
#include<ctime>
#include <cstdlib> 

using namespace std;


int findmax(string a[], int x)
{
	int index = 0;
	for (int i = 1; i < x; i++)
		if (a[i] > a[index])
			index = i;

	return index;
}

void Swap(string &a, string &b) {
	string temp = a;
	a = b;
	b = temp;
}

void sort(string a[], int x)
{
	for (int i = x - 1; i >= 0; i--)
		Swap(a[findmax(a, i)], a[i]);
}
int main()
{

	string A[5] = { "b","c","v","a","s" };
	for (int i = 0; i < 5; i++)
		cout << A[i] << endl;
	sort(A, 5);
	cout << endl;

	for (int i = 0; i < 5; i++)
		cout << A[i] << endl;

	system("pause");
	return 0;
}