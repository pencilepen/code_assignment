#include <iostream>
using namespace std;

struct ListNode
{

	double value;
	ListNode* next;


};

class NumberList
{
private:
	ListNode* head;
public:
	NumberList()
	{
		head = nullptr;
	}
	void appendNode(double);
	void displayList();
	void deleteNode(double);
	void removeLast();
};

void NumberList::removeLast()
{
	ListNode* nodePtr = nullptr;
	ListNode* previous = nullptr;
	if (!head)
		return;
	else
	{
		nodePtr = head;
		while (nodePtr->next)
		{
			previous = nodePtr;
			nodePtr = nodePtr->next;
		}
		delete nodePtr;
		previous->next = nullptr;
	}
	
}
void NumberList::deleteNode(double a)
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
void NumberList::displayList()
{
	ListNode* nodePtr;
	nodePtr = head;
	while (nodePtr)
	{
		cout << nodePtr->value << endl;
		nodePtr = nodePtr->next;
	}
}
void NumberList::appendNode(double a)
{
	ListNode* newNode;
	ListNode* nodePtr;

	if (!head)//If list is empty
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

int main()
{
	NumberList myList;
	myList.appendNode(4.6);
	myList.appendNode(6.6);
	myList.appendNode(3.3);
	myList.appendNode(5.9);

	myList.displayList();
	cout << "\n";
	//myList.deleteNode(3.3);
	//myList.displayList();

	myList.removeLast();
	myList.displayList();
	system("pause");
	return 0;
}