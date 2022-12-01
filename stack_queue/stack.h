#include <iostream>
#include "chain.h"
using namespace std;

//template<typename T> class Tstack {
//	T* pMem;
//	int sz;
//	int top;
//public:
//	Tstack() : top(-1), sz(0) { pMem = new T[0]; };
//	Tstack(const Tstack<T> & st) 
//	{
//		top = st.top;
//		sz = st.sz;
//			pMem = new T[st.top + 1];
//			std::copy(st.pMem, st.pMem + st.top + 1, pMem);
//	}
//
//	Tstack& operator=(const Tstack<T>& st)
//	{
//		if (this == &st) return *this;
//		if (!isempty()) delete []pMem;
//		top = st.top;
//		sz = st.sz;
//			pMem = new T[st.top + 1];
//			std::copy(st.pMem, st.pMem + st.top + 1, pMem);
//		return *this;
//	}
//
//	bool isempty() { return top == -1; }
//	bool isfull() { return top + 1 == sz; }
//	int height() { return top; }
//	void push(T obj)
//	{
//		if (isfull())
//		{
//			T* t;
//			T* tmp = new T[sz * 2 + 1];
//			std::copy(pMem, pMem + sz, tmp);
//			t = pMem;
//			pMem = tmp;
//			tmp = t;
//			sz = sz * 2 + 1;
//		}
//		pMem[++top] = obj;
//	}
//	T get()
//	{
//		if (isempty()) throw - 1;
//		return pMem[top];
//	}
//	void pop()
//	{
//		if (isempty()) throw - 1;
//		top--;
//	}
//	T ppull()
//	{
//		if (isempty()) throw - 1;
//		T tmp = pMem[top--];
//		return tmp;
//	}
//	~Tstack()
//	{
//		delete []pMem;
//	}
//};

template<typename T> class Tstack {
	chain<T>* firstptr;
public:
	Tstack() : firstptr(nullptr) {};
	Tstack(const Tstack<T>& st)
	{
		if (st.isempty()) { this->firstptr = nullptr; }
		else
		{
			firstptr = new chain<T>(st.firstptr->value);
			chain<T>* tmp1 = st.firstptr->nextptr;
			chain<T>* tmp2 = firstptr;
			while (tmp1 != nullptr)
			{
				tmp2->nextptr = new chain<T>(tmp1->value);
				tmp1 = tmp1->nextptr;
				tmp2 = tmp2->nextptr;
			}
		}
	}

	~Tstack()
	{
		while (firstptr != nullptr)
			pop();
	}

	Tstack& operator=(const Tstack<T>& st)
	{
		if (this == &st) return *this;
		if (st.isempty()) { this->firstptr = nullptr; }
		else
		{
			firstptr = new chain<T>(st.firstptr->value);
			chain<T>* tmp1 = st.firstptr->nextptr;
			chain<T>* tmp2 = firstptr;
			while (tmp1 != nullptr)
			{
				tmp2->nextptr = new chain<T>(tmp1->value);
				tmp1 = tmp1->nextptr;
				tmp2 = tmp2->nextptr;
			}
		}
		return *this;
	}

	bool isempty() const noexcept { return firstptr == nullptr; }
	void push(T obj)
	{
		chain<T>* tmp = new chain<T>(obj, firstptr);
		firstptr = tmp;
	}

	T get()
	{
		if (isempty()) throw - 1;
		return firstptr->value;
	}

	void pop()
	{
		if (isempty()) throw - 1;
		chain<T>* tmp = firstptr;
		firstptr = firstptr->nextptr;
		delete tmp;
	}

	T ppull()
	{
		if (isempty()) throw - 1;
		chain<T>* tmp = firstptr;
		T t = tmp->value;
		firstptr = firstptr->nextptr;
		delete tmp;
		return t;
	}
};