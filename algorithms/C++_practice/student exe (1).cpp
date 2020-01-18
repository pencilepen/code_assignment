#include <iostream>
#include <string>
using namespace std;

class Student
{
protected:
	string firstName;
	string lastName;
	string studentID;
	string phoneNumber;
	double gpa;
public:
	string getFirstNmae() const { return firstName; }
	const string getLastName() { return lastName; }
	string getStudentID() const { return studentID; }
	string getPhoneNumber() const { return phoneNumber; }
	double getGpa() const { return gpa; }

	void setFirstName(const string &a) { firstName = a; }
	void setLastName(const string &b) { lastName = b; }
	void setStudentID(const string &c) { studentID = c; }
	void setPhoneNumber(const string &d) { phoneNumber = d; }
	void setGpa(const double &e) { gpa = e; }

	Student()
	{
		firstName = " ";
		lastName = " ";
		studentID = " ";
		phoneNumber = " ";
		gpa = 0;
	}

	Student(const string &a, const string &b, const string &c, const string &d, const double &e)
	{
		firstName = a;
		lastName = b;
		studentID = c;
		phoneNumber = d;
		gpa = e;
	}

};

class Course
{
private:
	string code;
	int section;
	int capacity;
	int numStudents;
	Student *list;
public:
	string getCode() { return code; }
	int getSection() { return section; }
	int getCapacity() { return capacity; }
	int getNumStudents() { return numStudents; }

	void setCode(string f) { code = f; }
	void setSection(int g) { section = g; }


	Course()
	{
		code = "CMPT2300";
		section = 1;
		capacity = 35;
		numStudents = 0;
		list = new Student[35];
	}
	Course(string f, int g, int h)
	{
		code = f;
		section = g;
		capacity = h;
		numStudents = 0;
		list = new Student[h];
	}
	~Course()
	{
		delete[] list;
		list = nullptr;
	}
	void add(Student j)
	{
		if (numStudents >= capacity)
		{
			cout << "The course is full\n";
			return;
		}
		numStudents++;
		int z = numStudents - 2;
		while (z >= 0 && (j.getGpa() > list[z].getGpa()))
		{
			list[z + 1] = list[z];
			z--;
		}
		list[z + 1] = j;
	}
	void display()
	{
		for (int i = 0; i < numStudents; i++)
		{
			cout << list[i].getFirstNmae() << " " << list[i].getLastName() << "'s ID is "
				<< list[i].getStudentID() << "and phone number is "
				<< list[i].getPhoneNumber() << " whose GPA is " << list[i].getGpa() << endl;
		}
	}
	void display(string x, int y)
	{
		if (y == 1)
		{
			for (int i = 0; i < numStudents; i++)
			{
				if (x == list[i].getFirstNmae())
					cout << list[i].getFirstNmae() << "\t" << list[i].getLastName() << "\t"
					<< list[i].getStudentID() << "\t" << list[i].getPhoneNumber() << "\t"
					<< list[i].getGpa() << endl;
				//return;
			}
		}
		else if (y == 2)
		{
			for (int i = 0; i < numStudents; i++)
			{
				if (x == list[i].getLastName())
					cout << list[i].getFirstNmae() << "\t" << list[i].getLastName() << "\t"
					<< list[i].getStudentID() << "\t" << list[i].getPhoneNumber() << "\t"
					<< list[i].getGpa() << endl;
				//return;
			}
		}
		else if (y == 3)
		{
			for (int i = 0; i < numStudents; i++)
			{
				if (x == list[i].getStudentID())
					cout << list[i].getFirstNmae() << "\t" << list[i].getLastName() << "\t"
					<< list[i].getStudentID() << "\t" << list[i].getPhoneNumber() << "\t"
					<< list[i].getGpa() << endl;
				//return;
			}
		}
		else if (y == 4)
		{
			for (int i = 0; i < numStudents; i++)
			{
				if (x == list[i].getPhoneNumber())
					cout << list[i].getFirstNmae() << "\t" << list[i].getLastName() << "\t"
					<< list[i].getStudentID() << "\t" << list[i].getPhoneNumber() << "\t"
					<< list[i].getGpa() << endl;
				//return;
			}
		}
		else
			cout << "Wrong!\n";
	}
	void remove(string w, int v)
	{
		if (v == 1)
		{
			for (int i = 0; i < numStudents; i++)
			{
				if (w == list[i].getFirstNmae())
				{
					for (int u = i; u < numStudents - 1; u++)
						list[u] = list[u + 1];
					numStudents--;
				}
			}
		}
		else if (v == 2)
		{
			for (int i = 0; i < numStudents; i++)
			{
				if (w == list[i].getLastName())
				{
					for (int u = i; u < numStudents - 1; u++)
						list[u] = list[u + 1];
					numStudents--;
				}
			}
		}
		else if (v == 3)
		{
			for (int i = 0; i < numStudents; i++)
			{
				if (w == list[i].getStudentID())
				{
					for (int u = i; u < numStudents - 1; u++)
						list[u] = list[u + 1];
					numStudents--;
				}
			}
		}
		else if (v == 4)
		{
			for (int i = 0; i < numStudents; i++)
			{
				if (w == list[i].getPhoneNumber())
				{
					for (int u = i; u < numStudents - 1; u++)
						list[u] = list[u + 1];
					numStudents--;
				}
			}
		}
		else
			cout << "Wrong\n";

	}
};
int main()
{
	Student a("AA", "AA", "1111", "604-123", 3.4);
	Student b("BB", "BB", "2222", "604-223", 2.6);
	Student c("CC", "CC", "3333", "604-333", 3.8);
	Student d("DD", "DD", "4444", "604-423", 2.1);
	Student e("EE", "EE", "5555", "778-123", 2.8);
	Student f("FF", "FF", "6666", "778-456", 3.3);
	Course table("CMPT2300", 1, 35);
	table.add(a);
	table.add(b);
	table.add(c);
	table.add(d);
	table.add(e);
	table.add(f);
	table.display();

	cout << "\n\n";

	table.display("4444", 3);
	cout << "\n\n";
	table.remove("778-456", 4);
	table.display();

	system("pause");
	return 0;
}