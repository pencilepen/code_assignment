#include <iostream>
using namespace std;
int binarySearch(int array[], int first, int last, int target);

int main()
{
	int x[10]{0,1, 2, 4, 5, 6, 8,12,13,15};
	int target = 1;
	int index;

	index = binarySearch(x, 0, 9, target);
	if (index == -1)
		cout << "no\n";
	else
		cout << target << " = x[" << index <<"]"<< endl;

	system("pause");
	return 0;
}

int binarySearch(int array[], int first, int last, int target)
{
	int index;
	if (first > last)
		index = -1;
	else
	{
		int mid = (first + last) / 2;
		if (target == array[mid])
			index = mid;
		else if (target < array[mid])
			index = binarySearch(array, first, mid - 1, target);
		else
			index = binarySearch(array,  mid + 1,last, target);
	}
	return index;
}