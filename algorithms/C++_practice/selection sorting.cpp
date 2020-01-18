#include <iostream>
#include<string>
using namespace std;
void findmax(string sortArray[])
{
	int size=5;
	string maxEl;
	maxEl = sortArray[0];
	int t;

	while (size > 0)
	{
		t = 0;
		for (t; t < size; t++)
		{
			if (maxEl < sortArray[t])
			{
				maxEl = sortArray[t];
				
			}
		}
		int i;
		for (i = 0; i < 5; i++)
		{
			if (maxEl == sortArray[i])
				break;
		}
		for (i; i < size-2; i++)
		{
			sortArray[i] = sortArray[(i + 1)];
		}
		sortArray[size-1] = maxEl;
		size--;
	}
	
}
int main()
{
	string  sortArray[5] = { "s","g","d","h","e"};
	for (int i = 0; i < 5; i++)
	{
		cout << sortArray[i] << endl;
	}
	cout << endl;
	
	 findmax(sortArray);
	 for (int q = 0; q < 5; q++)
	 {
		 cout << sortArray[q] << endl;
	 }

	system("pause");
	return 0;

}