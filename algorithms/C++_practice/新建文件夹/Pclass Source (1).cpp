#include <iostream>
#include <string>
#include "Vector3d.h"
using namespace std;

template<class T>
T Sum(T, T);

int main()
{
	Vector3d *a;
	double *norms;
	int size;

	cout << "Enter size";
	cin >> size;

	a = new Vector3d[size];
	norms = new double[size];

	for (int i = 0; i < size; i++)
	{
		a[i].input();
		norms[i] = a[i].norm();
	}
	for (int i = 0; i < size; i++)
		cout << norms[i] << endl;

	delete [] a;
	delete [] norms;

	system("pause");
	return 0;
}

template <class T>
T Sum(T a, T b)
{
	return a + b;
}


