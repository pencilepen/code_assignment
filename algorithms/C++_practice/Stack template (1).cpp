#include <iostream>
using namespace std;

template <class T>
class Stack
{
private:
	T* stackArray;
	T  stackSize;
	T top;
public:
	Stack(T);
	//Stack(const IntStack &);
	~Stack();

	void push(T);
	void pop(T &);
	bool isFull() const;
	bool isEmpty() const;
	void display();
};
template <class T>
Stack<T>::Stack(T size)
{
	stackArray = new T[size];
	stackSize = size;
	top = -1;
}
template<class T>
Stack<T>::~Stack()
{
	delete[] stackArray;

}
template<class T>
void Stack<T>::push(T num)
{
	if (isFull())
		cout << "full\n";
	else
	{
		top++;
		stackArray[top] = num;
	}
}
template<class T>
void Stack<T>::pop(T &num)
{
	if (isEmpty())
		cout << "empty\n";
	else
	{
		num = stackArray[top];
		top--;
	}
}
template<class T>
bool Stack<T>::isFull() const
{
	//if (stackArray[stackSize])
	//return 1;
	if (top == (stackSize - 1))
		return 1;
	return 0;
}
template<class T>
bool Stack<T>::isEmpty() const
{
	//if (!stackArray[0])
	//return 1;
	if (top == -1)
		return 1;
	return 0;
}
template<class T>
void Stack<T>::display()
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
	Stack<int> a(4);
	a.push(10);
	a.push(14);
	a.push(15);
	a.push(18);
	a.push(24);
	a.display();

	int x;
	a.pop(x);
	cout << "item popped " << x << endl;
	cout << "new Stack\n";
	/////////////////////
	a.pop(x);
	cout << "item popped " << x << endl;
	a.pop(x);
	cout << "item popped " << x << endl;
	a.pop(x);
	cout << "item popped " << x << endl;
	a.pop(x);
	cout << "item popped " << x << endl;
	a.display();
	system("pause");
	return 0;
}