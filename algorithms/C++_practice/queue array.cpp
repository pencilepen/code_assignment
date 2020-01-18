#include <iostream>
using namespace std;

class IntQueue
{
private:
	int* queueArray;
	int queueSize;
	int front;
	int rear;
	int numItems;
public:
	IntQueue(int);
	~IntQueue();

	void enqueue(int);
	void dequeue(int &);
	bool isEmpty() const;
	bool isFull() const;
	void display();

};
IntQueue::IntQueue(int a)
{
	queueArray = new int[a];
	queueSize = a;
	front = -1;
	rear = -1;
	numItems = 0;
}
IntQueue::~IntQueue()
{
	delete[] queueArray;
}
bool IntQueue::isFull()const
{
	if (numItems<queueSize)
		return 0;
	else
		return 1;
}
bool IntQueue::isEmpty()const
{
	if (numItems)
		return 0;
	else 
		return 1;
}
void IntQueue::enqueue(int a)
{
	if (isFull())
		cout << "Full.\n";
	else
	{
		rear = (rear + 1) % queueSize;
		queueArray[rear] = a;
		numItems++;
	}
}
void IntQueue::dequeue(int &a)
{
	if (isEmpty())
		cout << "Empty.\n";

	else
	{
		front = (front + 1) % queueSize;
		a = queueArray[front];
		numItems--;
	}
}
/*void IntQueue::display()
{
	if (isEmpty())
	{
		cout << "Empty.\n";
		return;
	}
	if (rear > front)
	{
		for (int i = front + 1; i < rear; i++)
			cout << queueArray[i] << endl;
	}
	else
	{
		for (int t = front; t < numItems; t++)
			cout << queueArray[t] << endl;
		for (int u = rear; u > -1; u--)
			cout << queueArray[u] << endl;
	}
}
*/
void IntQueue::display()
{
	if (isEmpty())
	{
		cout << "Empty.\n";
		return;
	}
	cout << "these are the elements.\n";
	int i = front + 1;
	while (1)
	{
		cout << queueArray[i] << endl;
		if (i == rear)
			break;
		i = (i + 1) % queueSize;  
	}
}
int main()//for applying waitinglist
{
	int  a;
	IntQueue list(5);
	list.enqueue(1);
	list.enqueue(2);
	list.enqueue(3);
	list.enqueue(4);
	list.enqueue(5);
	list.display();
	cout << endl;
	list.dequeue(a);
	list.display();
	cout << endl;
	cout << "delete "<<a << endl;

	list.enqueue(10);//example of adding 

	cout << endl;
	list.dequeue(a);
	list.display();
	cout << endl;
	cout << "delete " << a << endl;

	cout << endl;
	list.dequeue(a);
	list.display();
	cout << endl;
	cout << "delete " << a << endl;

	cout << endl;
	list.dequeue(a);
	list.display();
	cout << endl;
	cout << "delete " << a << endl;

	system("pause");
	return 0;
}