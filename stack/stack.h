#include <iostream>
#include <vector>
using namespace std;

template<typename T> class Tstack {
	T* pMem;
	int sz;
	int top;
public:
	Tstack() : top(-1), sz(0) { pMem = new T[0]; };
	Tstack(const Tstack<T> & st) 
	{
		top = st.top;
		sz = st.sz;
			pMem = new T[st.top + 1];
			std::copy(st.pMem, st.pMem + st.top + 1, pMem);
	}

	Tstack& operator=(const Tstack<T>& st)
	{
		if (this == &st) return *this;
		if (!isempty()) delete []pMem;
		top = st.top;
		sz = st.sz;
			pMem = new T[st.top + 1];
			std::copy(st.pMem, st.pMem + st.top + 1, pMem);
		return *this;
	}

	bool isempty() { return top == -1; }
	bool isfull() { return top + 1 == sz; }
	int height() { return top; }
	void push(T obj)
	{
		if (isfull())
		{
			T* t;
			T* tmp = new T[sz * 2 + 1];
			std::copy(pMem, pMem + sz, tmp);
			t = pMem;
			pMem = tmp;
			tmp = t;
			sz = sz * 2 + 1;
		}
		pMem[++top] = obj;
	}
	T get()
	{
		if (isempty()) throw - 1;
		return pMem[top];
	}
	void pop()
	{
		if (isempty()) throw - 1;
		top--;
	}
	T ppull()
	{
		if (isempty()) throw - 1;
		T tmp = pMem[top--];
		return tmp;
	}
	~Tstack()
	{
		delete []pMem;
	}
};