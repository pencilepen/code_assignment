#include <iostream>
using namespace std;

class IntStack
{
private:
	int* stackArray;
	int  stackSize;
	int top;
public:
	IntStack(int);
	//IntStack(const IntStack &);
	~IntStack();

	void push(int);
	void pop(int &);
	bool isFull() const;
	bool isEmpty() const;
	void display();//cosnt;
};

IntStack::IntStack(int size)
{
	stackArray = new int[size];
	stackSize = size;
	top = -1;
}
IntStack::~IntStack()
{
	delete[] stackArray;

}
void IntStack::push(int num)
{
	if (isFull())
		cout << "full\n";
	else 
	{
		top++;
		stackArray[top] = num;
	}
}
void IntStack::pop(int &num)
{
	if (isEmpty())
		cout << "empty\n";
	else
	{
		num = stackArray[top];
		top--;
	}
}
bool IntStack::isFull() const
{
	//if (stackArray[stackSize])
		//return 1;
	if (top == (stackSize - 1))
		return 1;
	return 0;
}
bool IntStack::isEmpty() const
{
	bool status;
	//if (!stackArray[0])
		//return 1;
	if (top == -1)
		return 1;
	return 0;
}
void IntStack::display()//const
{
	if (isEmpty())
	{
		cout << "empty\n";
		return;

	}
	for (int i = 1; i <= top; i++)
		cout << stackArray[i] << endl;

}
int main()
{
	IntStack a(4);
	a.push(10);
	a.push(14);
	a.push(15);
	a.push(18);
	a.push(24);
	a.display();

	int x;
	a.pop(x);
	cout <<"item popped "<< x << endl;
	cout << "new Stack\n";
	a.display();
	system("pause");
	return 0;
}