#include <iostream>
#include <vector>
using namespace std;

template<typename T> class Tstack {
	vector<T> pMem;
	int top;
public:
	Tstack() : top(-1) {};
	bool isempty() { return top == -1; }
	void push(T obj)
	{
		pMem.push_back(obj);
		top++;
	}
	T pull()
	{
		if (isempty()) throw - 1;
		top--;
		T tmp = pMem.back();
		pMem.pop_back();
		return tmp;
	}
};

