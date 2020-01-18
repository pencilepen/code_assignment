#include <iostream>
using namespace std;

template <class T>
class ListNode
{
public:
	T value;           // The value in this node
	ListNode<T> *next;  // To point to the next node

	ListNode(T nodevalue)
	{
		value = nodevalue;
		next = nullptr;
	}
};

template <class T>
class NumberList
{
private:
	ListNode<T> *head;            // List head pointer
public:
	NumberList()
	{
		head = nullptr;
	}

	~NumberList();

	void appendNode(T);
	void deleteNode(T);
	void displayList() const;
};

template <class T>
void NumberList<T>::appendNode(T num)
{
	ListNode<T> *newNode;  // To point to a new node
	ListNode<T> *nodePtr;  // To move through the list

						// Allocate a new node and store num there.
	newNode = new ListNode<T>(num);
	newNode->value = num;
	newNode->next = nullptr;

	// If there are no nodes in the list
	// make newNode the first node.
	if (!head)
		head = newNode;
	else  // Otherwise, insert newNode at end.
	{
		// Initialize nodePtr to head of list.
		nodePtr = head;

		// Find the last node in the list.
		while (nodePtr->next)
			nodePtr = nodePtr->next;

		// Insert newNode as the last node.
		nodePtr->next = newNode;
	}
}

template <class T>
void NumberList<T>::displayList() const
{
	ListNode<T> *nodePtr;  // To move through the list

						// Position nodePtr at the head of the list.
	nodePtr = head;

	// While nodePtr points to a node, traverse
	// the list.
	while (nodePtr)
	{
		// Display the value in this node.
		cout << nodePtr->value << endl;

		// Move to the next node.
		nodePtr = nodePtr->next;
	}
}


//**************************************************
// The deleteNode function searches for a node     *
// with num as its value. The node, if found, is   *
// deleted from the list and from memory.          *
//**************************************************

template <class T>
void NumberList<T>::deleteNode(T num)
{
	ListNode<T> *nodePtr = nullptr;       // To traverse the list
	ListNode<T> *previousNode = nullptr;  // To point to the previous node

									   // If the list is empty, do nothing.
	if (!head)
		return;

	// Determine if the first node is the one.
	if (head->value == num)
	{
		nodePtr = head->next;
		delete head;
		head = nodePtr;
	}
	else
	{
		// Initialize nodePtr to head of list
		nodePtr = head;

		// Skip all nodes whose value member is
		// not equal to num.
		while (nodePtr != nullptr && nodePtr->value != num)
		{
			previousNode = nodePtr;
			nodePtr = nodePtr->next;
		}

		// If nodePtr is not at the end of the list,
		// link the previous node to the node after
		// nodePtr, then delete nodePtr.
		if (nodePtr)
		{
			previousNode->next = nodePtr->next;
			delete nodePtr;
		}
	}
}

//**************************************************
// Destructor                                      *
// This function deletes every node in the list.   *
//**************************************************

template <class T>
NumberList<T>::~NumberList()
{
	ListNode<T> *nodePtr;   // To traverse the list
	ListNode<T> *nextNode;  // To point to the next node

						 // Position nodePtr at the head of the list.
	nodePtr = head;

	// While nodePtr is not at the end of the list...
	while (nodePtr != nullptr)
	{
		// Save a pointer to the next node.
		nextNode = nodePtr->next;

		// Delete the current node.
		delete nodePtr;

		// Position nodePtr at the next node.
		nodePtr = nextNode;
	}
}

int main()
{
	NumberList<double> list;

	// Build the list with some values.
	list.appendNode(2.5);
	list.appendNode(7.9);
	list.appendNode(12.6);
	list.appendNode(3.6);

	// Display the list.
	cout << "Here are the initial values:\n";
	list.displayList();
	cout << endl;

	// Delete the middle node.
	cout << "Now deleting the node in the middle.\n";
	list.deleteNode(7.9);

	// Display the list.
	cout << "Here are the nodes left.\n";
	list.displayList();
	cout << endl;

	// Delete the last node.
	cout << "Now deleting the last node.\n";
	list.deleteNode(12.6);

	// Display the list.
	cout << "Here are the nodes left.\n";
	list.displayList();
	cout << endl;

	// Delete the only node left in the list.
	cout << "Now deleting the only remaining node.\n";
	list.deleteNode(2.5);

	// Display the list.
	cout << "Here are the nodes left.\n";
	list.displayList();

	system("pause");
	return 0;
}