#include <iostream>
using namespace std;

template<typename T> class Tqueue {
	int size, start, end;
	T* pMem;
	int next(int i) { return (i + 1) % size; }
public:
	Tqueue(int s) : size(s) { pMem = new T[size]; end = 0; start = next(end); };
	Tqueue(Tqueue& q) : size(q.size), end(q.end), start(q.start) { delete pMem; pMem = new T[size]; 
	for (int i = 0; i < size; i++)
		pMem = p.pMem;
	}
	Tqueue& operator=(Tqueue& q){
		if (this == &q) return *this;
		size = q.size;
		end = q.end;
		start = q.start;
		delete pMem; 
		pMem = new T[size];
		for (int i = 0; i < size; i++)
			pMem = q.pMem;
		return *this;
	}
	bool isempty() { return next(end) == start; }
	bool isfull() { return next(next(end)) == start; }
	void push(T obj)
	{
		if (isfull()) throw - 1;
		end = next(end);
		pMem[end] = obj;
	}
	T pull()
	{
		if (isempty()) throw - 1;
		T tmp = pMem[start];
			start++;
		return tmp;
	}
};