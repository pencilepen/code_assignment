#include <iostream>
using namespace std;

/*int position(int a[], int x)
{
	int index;
	for (int i = 0; i < x; i++)
	{
		if (a[unsorted] < a[i])
			index = i;
	}
	return index;
}*/

void insertion(int a[], int n)
{
	for (int unsorted = 1; unsorted < n; unsorted++)
	{
		int nextItem = a[unsorted];
		int loc = unsorted;
		while ((loc > 0) && (a[loc - 1] > nextItem))
		{
			a[loc] = a[loc - 1];
			loc--;
		}
		a[loc] = nextItem;
	}
}
int main()
{
	int mylist[5] = { 75,29,16,64,3 };
	for (int i = 0; i < 5; i++)
	{
		cout << mylist[i] << endl;
	}
	cout << endl;
	insertion(mylist, 5);
	for (int i = 0; i < 5; i++)
	{
		cout << mylist[i] << endl;
	}

	system("pause");
	return 0;
}