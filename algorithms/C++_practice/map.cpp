#include <iostream>
#include <string >
#include <iomanip>
using namespace std;

template<class K,class V>
class map
{
private:
	K* key;
	V* value;
	int numEntries;
	int capacity;
	
public:
	map(int size)
	{
		key = new K[size];
		value = new V[size];
		numEntries = 0;
		capacity = size;
	}
	~map()
	{
		delete[]key;
		delete[]value;
	}
	void addEntries(K k,V v)
	{
		if (numEntries == capacity)
		{
			cout << "FULL\n";
			return;
		}
		int index = -1;
		for (int i = 0; i < numEntries; i++)
		{
			if (key[i] == k)
			{
				index = i;
				value[i] = v;
				return;
			}
		}

		key[numEntries] = k;
		value[numEntries] = v;
		numEntries++;
	}
	void display()
	{
		cout << "        Key           Values		\n";
		cout << "0---------------------------------\n";
		for (int i = 0; i < numEntries; i++)
		{
			cout <<left<< setw(18) << key[i] << setw(10) << value[i] << endl;

		}
	}
	void search(K k)
	{
		cout << "KKKKKK\n";
		for (int i = 0; i <numEntries; i++)
		{
			if (key[i] == k)
			{
				cout << value[i] << endl;
				return;
			}
		}
		cout << "NO\n";
	}
	void remove(K k)
	{
		for (int i = 0; i < numEntries; i++)
		{
			if (key[i] == k)
			{
				while (i < numEntries)
				{
					key[i] = key[i + 1];
					value[i] = value[i + 1];
					i++;
				}
				
			}

		}
	}
};

int main()
{
	map<string,string> mylist(100);
	mylist.addEntries("Ann", "604-466-1348");
	mylist.addEntries("Bill", "152-235-1455");
	mylist.addEntries("Cici", "256-156-2364");
	mylist.addEntries("David", "784-102-1564");
	mylist.display();
	cout << endl;
	mylist.search("Cici");

	cout << endl;
	mylist.remove("Cici");
	mylist.display();

	
	system("pause");
	return 0;

}