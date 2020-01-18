#include <iostream>
using namespace std;

template <class T>
class linkNode
{
public:
	T value;
	linkNode<T>* next=nullptr;
};

template <class T>
class dynQueue
{
private:
	linkNode<T>* front, *rear;
public:
	dynQueue()
	{
		front = nullptr;
		rear = nullptr;
	}
	~dynQueue();
	bool isEmpty();
	void enqueue(T );
	void dequeue(T &);
	void display();
};
template <class T>
dynQueue<T>::~dynQueue()
{
	while (front->next)
	{
		rear = front;
		front = front->next;
		delete rear;
	}
	delete front;
}
template <class T>
bool dynQueue<T>::isEmpty()
{
	if (front)
		return 0;
	else
		return 1;
}
template <class T>
void dynQueue<T>::enqueue(T a)
{
	linkNode<T>* nodePtr;
	nodePtr = front;
	if (!front)
	{
		front = new linkNode<T>;
		front->value = a;
		front->next = nullptr;
	}
	else
	{
		while (nodePtr->next)
		{
			nodePtr = nodePtr->next;
		}
		rear = new linkNode<T>;
		rear->value = a;
		rear->next = nullptr;
		nodePtr->next = rear;
	}
}
template <class T>
void dynQueue<T>::dequeue(T & a)
{
	if (isEmpty())
	{
		cout << "Empty.\n";
	}
	else
	{
		linkNode<T>* nodePtr;
		nodePtr = front;
		a = nodePtr->value;
		front = front->next;
		delete nodePtr;
	}
}
template <class T>
void dynQueue<T>::display()
{
	linkNode<T>* nodePtr;
	nodePtr = front;
	while (nodePtr)
	{
		cout << nodePtr->value << endl;
		nodePtr = nodePtr->next;
	}
}
int main()
{
	int a;
	dynQueue<int> mylist;
	mylist.enqueue(1);
	mylist.enqueue(2);
	mylist.enqueue(3);
	mylist.enqueue(4);
	mylist.display();
	cout << endl;

	mylist.dequeue(a);
	cout << "Delete " << a << endl;
	mylist.display();
	cout << endl;
	mylist.dequeue(a);
	cout << "Delete " << a << endl;
	mylist.display();
	cout << endl;
	mylist.dequeue(a);
	cout << "Delete " << a << endl;
	mylist.display();
	cout << endl;
	mylist.dequeue(a);
	cout << "Delete " << a << endl;
	mylist.display();
	cout << endl;
	mylist.dequeue(a);
	cout << "Delete " << a << endl;
	mylist.display();
	cout << endl;
	

	system("pause");
	return 0;
}