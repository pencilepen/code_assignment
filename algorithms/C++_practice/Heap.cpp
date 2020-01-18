#include <iostream>
#include <string>
using namespace std;

class HeapItem

{

private:
	int key;
	string name;
public:
	HeapItem()
	{
		key = 0;
		name = " ";
	}
	HeapItem(int k, string s)
	{
		name = s;
		key = k;
	}
	int getKey() { return key; }
	string getName() { return name; }
	void setKey(int x) { key = x; }
	void setNmae(string s) { name = s; }
};

class Heap

{
private:
	HeapItem* elements;
	int numElements;
	int heapLength;
public:
	Heap();
	Heap(int);
	~Heap();
	bool addItem(int, string);
	void reheapUp(int root, int bottom);
	//void swap(int a, int b);
	void removeRoot();
	void display();
};

Heap::Heap()
{
	elements = new HeapItem[10];
	numElements = 0;
	heapLength = 10;
}
Heap::Heap(int size)
{
	elements = new HeapItem[size];
	numElements = 0;
	heapLength = size;
}

Heap::~Heap()
{
	delete[] elements;
}

bool Heap::addItem(int key, string name)
{
	if (numElements >= heapLength)
		return false;
	HeapItem temp(key, name);
	elements[numElements] = temp;
	reheapUp(0, numElements);
	numElements++;
}

//void Heap::swap(int a, int b)
//{
//	HeapItem tempR = elements[a];
//	elements[a] = elements[b];
//	elements[b] = tempR;
//}
void Heap::reheapUp(int root, int bottom)
{
	int parent;
	if (bottom > root)
	{
		parent = (bottom - 1) / 2;
		if (elements[parent].getKey() < elements[bottom].getKey())
		{
			swap(elements[parent], elements[bottom]);
			reheapUp(root, parent);
		}
	}
}

void Heap::removeRoot()
{
	//x = elements[0].getKey;
	//cout << x << endl;

	swap(elements[0], elements[numElements-1]);
	numElements--;

	reheapUp(0, numElements);
}
void Heap::display()
{
	//cout << elements[0].getKey() <<"\t" << elements[numElements].getKey() << "\t" << numElements << endl;
	for (int i = 0; i < numElements; i++)
	{
		
		cout << elements[i].getKey()<<"\t"<<elements[i].getName() << endl;
	}
}


int main()
{
	Heap mylist;
	mylist.addItem(34, "Joker");
	mylist.addItem(26, "Bob");
	mylist.addItem(3, "King");
	mylist.addItem(54, "Park");
	mylist.addItem(13, "Fall");
	mylist.addItem(21, "Pizza");

	
	mylist.display();
	cout << endl;

	mylist.removeRoot();
	mylist.display();

	system("pause");
	return 0;
}