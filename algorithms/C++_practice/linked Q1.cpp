#include <iostream>
using namespace std;

class ListNode
{
public:
	int value;
	ListNode* next;
};
class NumList
{
private:
	ListNode* head;
public:
	NumList()
	{
		head = nullptr;
	}
	void appendNode(int);
	void deleteNode(int);
	~NumList();
	void display();
	void reverse();
	int search(int);
	void insert(int, int);
};
void NumList::appendNode(int a)
{
	ListNode* newNode;
	ListNode* nodePtr;

	if (!head)
	{
		head = new ListNode;
		head->value = a;
		head->next = nullptr;
	}
	else
	{
		newNode = new ListNode;
		newNode->value = a;
		newNode->next = nullptr;

		nodePtr = head;
		while (nodePtr->next)
		{
			nodePtr = nodePtr->next;
		}
		nodePtr->next = newNode;
	}
}
void NumList::deleteNode(int a)
{
	ListNode* nodePtr = nullptr;
	ListNode* previous = nullptr;
	if (!head)
		return;
	if (head->value == a)
	{
		nodePtr = head->next;
		delete head;
		head = nodePtr;

	}
	else
	{
		nodePtr = head;
		while (nodePtr != nullptr&&nodePtr->value != a)
		{
			previous = nodePtr;
			nodePtr = nodePtr->next;
		}
		if (nodePtr)
		{
			previous->next = nodePtr->next;
			delete nodePtr;
		}
	}

}
NumList::~NumList()
{
	ListNode* nodePtr;
	ListNode* followPtr;
	nodePtr = head;
	while (nodePtr != nullptr)
	{
		followPtr = nodePtr->next;
		delete nodePtr;
		nodePtr = followPtr;
	}
}
void NumList::display()
{
	ListNode* nodePtr;
	nodePtr = head;
	while (nodePtr)
	{
		cout << nodePtr->value << endl;
		nodePtr = nodePtr->next;
	}
}
void NumList::reverse()
{
	ListNode* nodePtr=nullptr;
	ListNode* followPtr=nullptr;
	ListNode* previous=nullptr;
	if (!head)
		return;
	nodePtr = head->next;
	
	if (head->value < nodePtr->value)
	{
		followPtr = nodePtr->next;
		previous = followPtr->next;
		head->next = followPtr;
		followPtr->next = nodePtr;
		nodePtr->next = previous;
	}
	do
	{
		previous = nodePtr;
		nodePtr = nodePtr->next;
		nodePtr->next = followPtr;
		if (nodePtr->value < followPtr->value)
		{
			nodePtr->next = followPtr->next;
			previous->next = followPtr;
			followPtr->next = nodePtr;
		}
	} while (followPtr->next);
}
int NumList::search(int a)
{
	ListNode* indexPtr;
	ListNode* nodePtr;
	if (!head)
		return -1;
	else if (head->value == a)
		return 0;
	else
	{
		indexPtr = head;
		int i = 0;
		while (indexPtr->next)
		{
			indexPtr = indexPtr->next;
			i++;
		}
		int g = 0;
		nodePtr = head;
		while (nodePtr->next)
		{
			nodePtr = nodePtr->next;
			g++;
			if (nodePtr->value == a)
			{
				return g;
				g--;
			}
		}
		if (g = i)
		{
			return -1;
		}
	}
}
void NumList::insert(int a, int b)
{
	ListNode* previous = nullptr;
	ListNode* indexPtr;
	ListNode* nodePtr;
	indexPtr = head;
	int i = 0;
	while (indexPtr->next)
	{
		indexPtr = indexPtr->next;
		i++;
	}
	delete[] indexPtr;
	indexPtr = new ListNode;//?????????????????????????????
	nodePtr = head;
	if (a == 0)
	{
		head = new ListNode;
		head->value = b;
		head->next = nodePtr;
	}
	else if (a >= i)
	{
		while (nodePtr->next)
			nodePtr = nodePtr->next;
		indexPtr->value = b;
		nodePtr->next = indexPtr;
	}
	else
	{
		for (int h = 0; h < a; h++)
		{
			previous = nodePtr;
			nodePtr = nodePtr->next;
		}
		indexPtr->value = b;
		indexPtr->next = nodePtr;
		previous->next = indexPtr;
	}
}

int main()
{
	NumList myList;
	myList.appendNode(9);
	myList.appendNode(49);
	myList.appendNode(3);
	myList.appendNode(87);
	myList.appendNode(15);
	myList.appendNode(6);
	myList.display();

	myList.reverse();
	myList.display();

	cout << "It deletes 15.\n";
	myList.deleteNode(15);
	myList.display();

	cout << "It searches 49.\n";
	cout<<"The position of 49 is "<<myList.search(49)<<" .\n";

	cout << "It inserts a number 1 to the third position.\n";
	myList.insert(3, 1);
	myList.display();
	
	myList.~NumList();
	system("pause");
	return 0;
}