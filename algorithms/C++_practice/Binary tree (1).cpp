#include<iostream>
using namespace std;
class linkCode
{
public:
	int value;
	linkCode* left=nullptr;
	linkCode* right=nullptr;
};

class IntBinaryTree
{
protected:
	linkCode* root;
public:
	IntBinaryTree()
	{
		root = nullptr;
	}
	void insertNode(int a)
	{
		linkCode*newNode = new linkCode;
		newNode->value = a;
		estimate(root, newNode);
	}
	void estimate(linkCode *& nodePtr,linkCode*&newNode)
	{
		if (nodePtr == nullptr)
			nodePtr = newNode;
		else if (newNode->value < nodePtr->value)
			estimate(nodePtr->left, newNode);
		else
			estimate(nodePtr->right, newNode);

	}

	void searh(int num)
	{
		linkCode* nodePtr;
		nodePtr = root;
		while (nodePtr)
		{
			if (num == nodePtr->value)
			{
				cout << num << " is here.\n";
				return;
			}
			else if (num < nodePtr->value)
				nodePtr = nodePtr->left;
			else 
				nodePtr = nodePtr->right;
		}
		cout << "no is not in the tree. \n";
	}

	void  display(linkCode* nodePtr)
	{
		if (nodePtr != nullptr)
		{
			display(nodePtr->left);
			cout << nodePtr->value << endl;
			display(nodePtr->right);
		}

	}
	void display()
	{
		display(root);
	}

};


int main() 
{
	IntBinaryTree mylist;
	mylist.insertNode(95);
	mylist.insertNode(16);
	mylist.insertNode(53);
	mylist.insertNode(10);
	mylist.insertNode(5);

	mylist.searh(16);
	mylist.searh(26);
	cout << endl;


	mylist.display();

	system("pause");
	return 0;
}