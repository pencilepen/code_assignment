#include<iostream>
using namespace std;

const int MAX_SIZE=10;

void merge(int thearray[], int first, int mid, int last)
{
	int tempArray[MAX_SIZE];
	int first1 = first;
	int last1 = mid;
	int first2 = mid + 1;
	int last2 = last;

	int index = first1;

	while ((first1 <= last1) && (first2 <= last2))
	{
		if (thearray[first1] <= thearray[first2])
		{
			 tempArray[index] = thearray[first2];
			 first1++;
		}
		else
		{
			tempArray[index] = thearray[first2];
			first2++;
		}
		index++;
	}
	while (first1 <= last1)
	{
		tempArray[index] = thearray[first1];
		first1++;
		index++;
	}
	while (first2 <= last2)
	{
		tempArray[index] = thearray[first2];
		first2++;
		index++;
	}
	for (index = first; index <= last; index++)
	{
		thearray[index] = tempArray[index];
	}
}

int main()
{
	int mylist[] = { 56,456,469,1,3658,23,31,8,47,36 };
	for (int i = 0; i < 5; i++)
	{
		cout << mylist[i] << endl;
	}
	merge(mylist, 0, 5, 9);
	for (int i = 0; i < 5; i++)
	{
		cout << mylist[i] << endl;
	}

	system("pause");
	return 0;
}