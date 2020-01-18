#include <iostream>
#include <string>
using namespace std;

class GameEntry
{
protected:
	string names;
	int score;
public:
	string getNames() const { return names; }
	int getScore() const { return score; }
	void setNames(const string &n) { names=n; }
	void setScore(const int &s) { score=s; }
	GameEntry()
	{
		names = "   ";
		score = 0;
	}
	GameEntry(const string &n, const int &s)
	{
		names = n;
		score = s;

	}
};
class Scores
{
private:
	int maxEntries;
	int numEntries;
	GameEntry *entries;
public:
	Scores()
	{
		maxEntries = 10;
		numEntries = 0;
		entries = new GameEntry[10];

	}
	Scores(int m)
	{
		maxEntries = m;
		numEntries = 0;
		entries = new GameEntry[m];
	}
	~Scores()
	{
		delete[]entries;
		entries = nullptr;
	}
};
int main()
{
	GameEntry x("Ho Chen", 450);
	cout << "Name: " << x.getNames() << endl;
	cin.ignore();
	return 0;
}