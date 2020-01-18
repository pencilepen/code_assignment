#include <iostream>
using namespace std; 
int fib(int);
int main()
{
	int *array=nullptr;
	int size;
	cout << "enter the size of array\n";
	cin >> size;

	array = new int[size];
	for (int i = 0; i < size; i++)
	{
		cin >> array[i];
	}
	for (int n=size;n>0;n--)
		cout << array[];

	system("pause");
	return 0;
}

//array[i]=narray[size]
//i+1=size-1
/*void backw(int a[],int size)
	if (size==0)
		return;
	else
	{
		cout<<a[size-1]<<endl;
		backw(a,size-1);
	}
*/