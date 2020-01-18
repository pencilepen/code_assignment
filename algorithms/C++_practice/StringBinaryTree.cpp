#include<iostream>
#include <string>
using namespace std;
class TreeNode
{
public:
	string value;
	TreeNode* left = nullptr;
	TreeNode* right = nullptr;
};

class StringBinaryTree
{
private:
	TreeNode* root;

	void insert(TreeNode *& nodePtr, TreeNode*&newNode)
	{
		if (nodePtr == nullptr)
			nodePtr = newNode;
		else if (newNode->value < nodePtr->value)
			insert(nodePtr->left, newNode);
		else
			insert(nodePtr->right, newNode);

	}
	void desSubTree(TreeNode* nodePtr)
	{
		if (nodePtr != nullptr)
		{
			if (nodePtr->left)
				desSubTree(nodePtr->left);
			if (nodePtr->right)
				desSubTree(nodePtr->right);
			delete nodePtr;
		}

	}
	void deleteNode(string num, TreeNode* &nodePtr)
	{
		if (num < nodePtr->value)
			deleteNode(num, nodePtr->left);
		else if (num > nodePtr->value)
			deleteNode(num, nodePtr->right);
		else
			makeDeletion(nodePtr, num);
	}
	void makeDeletion(TreeNode*&nodePtr, string num)
	{
		TreeNode* tempNodePtr = nullptr;
		if (nodePtr == nullptr)
			cout << "Cannot./n";
		else if (nodePtr->right == nullptr)
		{
			tempNodePtr = nodePtr;
			nodePtr = nodePtr->left;
			delete tempNodePtr;
		}
		else if (nodePtr->left == nullptr)
		{
			tempNodePtr = nodePtr;
			nodePtr = nodePtr->right;
			delete tempNodePtr;
		}
		else
		{
			tempNodePtr = nodePtr;
			nodePtr = nodePtr->right;
			while (nodePtr->left != nullptr)
				nodePtr = nodePtr->left;
			nodePtr->left = tempNodePtr->left;
			delete tempNodePtr;
		}
	}
	void displayInOrder(TreeNode* nodePtr) const
	{
		if (nodePtr != nullptr)
		{
			displayInOrder(nodePtr->left);
			cout << nodePtr->value << endl;
			displayInOrder(nodePtr->right);
		}

	}
	void displayPreOrder(TreeNode* nodePtr) const
	{
		if (nodePtr != nullptr)
		{
			cout << nodePtr->value << endl;
			displayPreOrder(nodePtr->left);
			displayPreOrder(nodePtr->right);
		}
	}
	void displayPostOrder(TreeNode* nodePtr)const
	{
		if (nodePtr != nullptr)
		{
			displayPostOrder(nodePtr->left);
			displayPostOrder(nodePtr->right);
			cout << nodePtr->value << endl;
		}
	}

public:
	StringBinaryTree()
	{
		root = nullptr;
	}
	~StringBinaryTree()
	{
		desSubTree(root);
	}

	void insertNode(string a)
	{
		TreeNode*newNode = new TreeNode;
		newNode->value = a;
		insert(root, newNode);
	}
	void searhNode(string num)
	{
		TreeNode* nodePtr;
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
	void remove(string num)
	{
		deleteNode(num, root);
	}
	void displayInOrder() const
	{
		displayInOrder(root);
	}
	void displayPreOrder() const
	{
		displayPreOrder(root);

	}
	void displayPostOrder() const
	{
		displayPostOrder(root) ;
	}
};


int main()
{
	StringBinaryTree mylist;
	mylist.insertNode("agks");
	mylist.insertNode("sdfgh");
	mylist.insertNode("sdhd");
	mylist.insertNode("pwei");
	mylist.insertNode("dfsa");
	mylist.insertNode("bfsd");

	mylist.searhNode("dfsa");
	cout << endl;

	mylist.displayInOrder();
	cout << endl;
	mylist.remove("dfsa");
	mylist.displayInOrder();

	system("pause");
	return 0;
}