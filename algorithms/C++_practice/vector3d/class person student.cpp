#include<iostream>
#include <string>
using namespace std;

void func();
class person
{
protected:
	string fullname;
	int byear;
public:
	string getFullname() { return fullname; }
	int getByear() { return byear; }
	void setFullname(string a) { fullname = a; }
	void setByear(int b) { byear = b; }
	person();
	person(string, int);
	void input();
	void output();
};

person::person()
{
	fullname = "123";
	byear = 123;
}
person::person(string x, int y)
{
	fullname = x;
	byear = y;
}
void person::input()
{
	cout << "Enter your full name.\n";
	cin >> fullname;
	cout << "Enter your brith year.\n";
	cin >> byear;
}
void person::output()
{
	cout << "YOUR ARE " << fullname << " brith in " << byear << "and"<<".\n";
}

class student:public person//private/ protected
{
private:
	double gpa;
public:
	double getGPA() { return gpa; }
	void setGPA(double z) { gpa = z; }
	student() 
	{//fullneame =
		gpa = 4; }
	void output()
	{
		cout << "YOUR ARE " << fullname << " brith in " << byear << " and GPA = " << gpa << endl;
	}
};

int main()
{
	student a;
	a.output();
	func(a);
	system("pause");
	return 0;
}

void func(person x)
{
	x.output();
}