#include <string>
#include <math.h.>
#include <iostream>
#include "Vector3d.h"
using namespace std;

double Vector3d::getX()
{
	return x;
}
double Vector3d::getY()
{
	return y;
}
double Vector3d::getZ()
{
	return z;
}
void Vector3d::setX(double a)
{
	x = a;
}
void Vector3d::setY(double a)
{
	y = a;
}
void Vector3d::setZ(double a)
{
	z = a;
}
void Vector3d::input()
{
	cout << "X? ";
	cin >> x;
	cout << "Y? ";
	cin >> y;
	cout << "Z? ";
	cin >> z;
}
void Vector3d::output()
{
	cout << "The vector coordinates: " << "( " << x << ", " << y << ", "
		<< z << ")" << endl;
}
Vector3d::Vector3d(double a, double b, double c)
{
	x = a;
	y = b;
	z = c;
}
Vector3d::Vector3d()
{
	x = y = z = 0;
}

/*double Vector3d::norm(Vector3d v)
{
	return sqrt(pow(v.getX(), 2.0) + pow(v.getY(), 2.0) + pow(v.getZ(), 2.0));
}*/

Vector3d::~Vector3d()
{
	cout << "Destroying a vector\n";
}

Vector3d operator+ (Vector3d a, Vector3d b)
{
	Vector3d c;
	c.setX(a.getX() + b.getX());
	c.setY(a.getY() + b.getY());
	c.setZ(a.getZ() + b.getZ());
	return c;
}

Vector3d operator- (Vector3d a, Vector3d b)
{
	Vector3d c;
	c.setX(a.getX() - b.getX());
	c.setY(a.getY() - b.getY());
	c.setZ(a.getZ() - b.getZ());
	return c;
}

double norm(Vector3d a)
{
	return sqrt(pow(v.getX(), 2.0) + pow(v.getY(), 2.0) + pow(v.getZ(), 2.0));
}

//defined member
/*double Vector3d::norm()
{
return sqrt(x*x+y*y+z*z);
}*/