#include <iostream>
#include <math.h.>
#include <string>
#include "Vector3d.h"
using namespace std;

int main()
{
	

	int a = 7, b = 8;
	cout << Sum(a, b) << endl;

	double c = 7.5, d = 8.5;
	cout << Sum(c, d) << endl;
	
	string e = "Hello", f = "World";
	cout << Sum(e, f) << endl;
	///////////////////////////////////////////
	Vector3d *a = nullptr;
	Vector3d c;
	a = &c;

	cout << c.getX() << endl;
	cout << a->getX() << endl;
	cout << a->norm() << endl;

	//////////////////////////////////////////////next topic
	/*Vector3d *a;
	double *norms;
	int size;

	cout << "enter size";
	cin >> size;

	a = new Vector3d[size];
	norms = new double[size];

	for (int i; i < size; i++)
		cout << norms[i] < , endl;
	delete[] a;
	delete[] norms;
	system("pause");
	return 0;*/
	//////////////////////////////////////////////////

	Vector3d g(1, 2, 3), h(1, 6, 8), i;
	i = Sum(g,h);
	i.output();

	cout << norm(g) << endl;
	system("pause");
	return 0;
}

template <class T>
T Sum(T a, T b)
{
	return a + b;
}
