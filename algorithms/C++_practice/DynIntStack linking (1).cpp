#include <iostream>
using namespace std;
class DynIntStack
{
private:
	struct StackNode
	{
		int value;
		StackNode* next;
	};
	StackNode* top;
public:
	DynIntStack()
	{
		top = nullptr;
	}
	~DynIntStack();
	void push(int);
	void pop(int &);
	bool isEmpty();
	void display();
};

DynIntStack::~DynIntStack()
{
	StackNode* nodePtr;
	StackNode* nextPtr;
	nodePtr = top;
	while (nodePtr != nullptr)
	{
		nextPtr = nodePtr->next;
		delete nodePtr;
		nodePtr = nextPtr;
	}
}
void DynIntStack::push(int a)
{
	StackNode* newNode = nullptr;
	newNode = new StackNode;
	newNode->value = a;

	if (isEmpty())
	{
		newNode->next = nullptr;
		top = newNode;
	}
	else
	{
		
		newNode->next = top;
	//delete[] top;
		top = newNode;
	}
	
}
void DynIntStack::pop(int &a)
{
	StackNode* nodePtr;
	if (!top)
	{
		cout << "Empty\n";
	}
	else
	{
		a = top->value;
		nodePtr = top->next;
		delete top;
		top = nodePtr;
		/*StackNode* nodePtr;
		nodePtr = top;
		nodePtr = nodePtr->next;
		delete[] top;
		top = nodePtr;*/
	}
}
bool DynIntStack::isEmpty()
{
	
	if (!top)
		return 1;
	else
		return 0;
}
void DynIntStack::display()
{
	if (isEmpty())
	{
		cout << "empty\n";
		return;
	}
	else
	{
		StackNode* nodePtr;
		nodePtr = top;
		while (nodePtr)
		{
			cout << nodePtr->value << endl;
			nodePtr = nodePtr->next;
		}
	}
	
}
int main()

{
	int popnum;
	DynIntStack list;
	list.push(5);
	list.push(15);
	list.push(53);
	list.push(95);
	list.push(16);
	list.push(34);
	list.display();
	cout << "popping .....\n";
	list.pop(popnum);
	cout << popnum << endl;
	list.pop(popnum);
	cout << popnum << endl;
	list.pop(popnum);
	cout << popnum << endl;
	list.pop(popnum);
	cout << popnum << endl;
	list.pop(popnum);
	cout << popnum << endl;
	list.pop(popnum);
	cout << popnum << endl;

	system("pause");
	return 0;
}