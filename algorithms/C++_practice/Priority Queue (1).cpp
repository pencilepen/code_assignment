#include<iostream>
#include<string>
using namespace std;
struct node
{
	string name;
	double fare;
	int point;
	node* link;
};
class Priority
{
private:
	node* front;
public:
	Priority();
	~Priority();
	void insert(string ,double,int);
	void deleteMin();
	void display();
	void lastNode();
	double cValue(int point,double fare);
};

Priority::Priority()
{
	string name = "AAA";
	double fare = 0;
	int point = 0;
	node* link = nullptr;
}
Priority::~Priority()
{
	while (front)
		lastNode();
}
void Priority::lastNode()
{
	node* nodePtr;
	nodePtr = front;
	while (nodePtr->link)
		nodePtr = nodePtr->link;
	delete nodePtr;
}
/*void Priority::insert(string a, double b)
{
	node* nodePtr;
	nodePtr = front;
	node* temp = nullptr;

	node* newNode;
	newNode = new node;
	newNode->name = a;
	newNode->fare = b;
	newNode->link = nullptr;

	if (!front)
		front = newNode;
	else
	{
		if (nodePtr->fare > newNode->fare)
		{
			front = newNode;
			newNode->link = nodePtr;
		}
		else
		{
			while (newNode->fare > nodePtr->fare)
			{
				temp = nodePtr;
				nodePtr = nodePtr->link;
			}
			temp->link = newNode;
			newNode->link = nodePtr;	
		}
	}
}*/

void Priority::insert(string N, double F,int P)
{
	node *temp, *q;
	temp = new node;
	temp->name = N;
	temp->fare = F;
	temp->point = P;
	if (front == nullptr || F < cValue(front->point,front->fare))//front->fare)
	{
		temp->link = front;
		front = temp;
	}
	else
	{
		q = front;
		while (q->link != nullptr &&cValue(q->link->point,q->link->fare)<=F)//q->link->fare <= F)
			q = q->link;
		temp->link = q->link;
		q->link = temp;
	}
}
void Priority::display()
{
	cout << "Name\t" <<"Point\t"<< "Fare\n";
	cout << "_________________________________________________________\n";

	node* nodePtr;
	nodePtr = front;
	while (nodePtr)
	{
		cout << nodePtr->name << "\t"<<nodePtr->point <<"\t"<< nodePtr->fare << endl;
		nodePtr = nodePtr->link;
	}
}
void Priority::deleteMin()
{
	node* nodePtr;
	nodePtr = front;
	front = nodePtr->link;
	delete nodePtr;
}

double Priority::cValue(int point,double fare)
{
	double c;
	c = 0.5*point + 0.5 + fare;
	return c;
}
int main()
{
	Priority mylist;
	mylist.insert("Douglas", 4.8,3);
	mylist.insert("Ann", 3.2,10);
	mylist.insert("CiCi", 5.6,5);
	mylist.insert("Bell", 2.4,31);
	mylist.insert("Daivd", 1.3,17);
	mylist.display();

	cout << endl;
	mylist.deleteMin();
	mylist.display();

	system("pause");
	return 0;
}
///c=0.5*point+0.5+fare;