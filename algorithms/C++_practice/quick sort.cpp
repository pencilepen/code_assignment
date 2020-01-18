#include<iostream>

using namespace std;

void quicksort(int number[], int first, int last)
{
	int f, l, temp, pivot;
	if (first < last)
	{
		 pivot = first;
		 f = first;
		 l = last;
		
		while (f < l)
		{
			while (number[f] <= number[pivot] && f < last)
				f++;
			while (number[l] > number[pivot])
				l--;
			if (f < l)
			{
				temp = number[f];
				number[f] = number[l];
				number[l] = temp;
			}
		}
		
		temp = number[pivot];
		number[pivot] = number[l];
		number[l] = temp;
		quicksort(number, first, l - 1);
		quicksort(number, l + 1, last);
	}
}

int main() {
	int count;
	int *number = nullptr;

	cout << "How many elements you want to enter?: ";
	cin >> count;

	number = new int[count];
	cout << "Enter " << count << " elements: " << endl;
	for (int i = 0; i<count; i++)
		cin >> number[i];

	quicksort(number, 0, count - 1);

	cout << "These are sorted elements: \n";
	for (int i = 0; i<count; i++)
		cout << number[i] << endl;

	delete[] number;

	system("pause");

	return 0;
}