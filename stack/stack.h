#include <iostream>
#include <vector>
using namespace std;

template<typename T> class Tstack {
	vector<T> pMem;
	int top;
public:
	Tstack() : top(-1) {};
	bool isempty() { return top == -1; }
	int height() { return top; }
	void push(T obj)
	{
		pMem.push_back(obj);
		top++;
	}
	T get()
	{
		if (isempty()) throw - 1;
		return pMem.back();
	}
	void pop()
	{
		if (isempty()) throw - 1;
		pMem.pop_back();
		top--;
	}
	T ppull()
	{
		if (isempty()) throw - 1;
		T tmp = pMem.back();
		pop();
		return tmp;
	}
};

