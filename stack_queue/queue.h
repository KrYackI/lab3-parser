#pragma once
#include <iostream>
#include "chain.h"
using namespace std;

//template<typename T> class Tqueue {
//	Tstack<T> left, right;
//	size_t sz;
//public:
//	Tqueue() : sz(0) { };
//	bool isempty() { return left.isempty() && right.isempty(); }
//	bool isfull() { return left.isfull() && right.isfull(); }
//	void push(T obj)
//	{
//		left.push(obj);
//		sz++;
//	}
//	void pop()
//	{
//		if (isempty()) throw - 1;
//		if (right.isempty())
//		{
//			while (!left.isempty())
//				right.push(left.ppull());
//		}
//		right.pop();
//		sz--;
//	}
//	//T last()
//	//{
//	//	if (isempty()) throw - 1;
//	//	return pMem[end];
//	//}
//	T front()
//	{
//		if (isempty()) throw - 1;
//		if (right.isempty())
//		{
//			while (!left.isempty())
//				right.push(left.ppull());
//		}
//		return right.get();
//	}
//};

template<typename T> class Tqueue {
	chain<T>* firstptr;
	chain<T>* lastptr;
public:
	Tqueue() : firstptr(nullptr), lastptr(nullptr) {};
	Tqueue(const Tqueue& q)
	{
		if (q.isempty()) { this->firstptr = this->lastptr = nullptr;}
		else
		{
			firstptr = new chain<T>(q.firstptr->value);
			chain<T>* tmp1 = q.firstptr->nextptr;
			chain<T>* tmp2 = firstptr;
			while (tmp1 != nullptr)
			{
				tmp2->nextptr = new chain<T>(tmp1->value);
				tmp1 = tmp1->nextptr;
				tmp2 = tmp2->nextptr;
			}
			lastptr = tmp2;
		}
	}

	~Tqueue()
	{
		while (firstptr != nullptr)
			pop();
	}

	Tqueue& operator=(const Tqueue& q)
	{
		if (this == &q) return *this;
		if (q.isempty()) { this->firstptr = this->lastptr = nullptr; return *this; }
		firstptr = new chain<T>(q.firstptr->value);
		chain<T>* tmp1 = q.firstptr->nextptr;
		chain<T>* tmp2 = firstptr;
		while (tmp1 != nullptr)
		{
			tmp2->nextptr = new chain<T>(tmp1->value);
			tmp1 = tmp1->nextptr;
			tmp2 = tmp2->nextptr;
		}
		lastptr = tmp2;
		return *this;
	}

	bool isempty() const noexcept { return firstptr == nullptr; }

	void push(T obj)
	{
		chain<T>* tmp = new chain<T>(obj);
		if (!isempty())
		{
			lastptr->nextptr = tmp;
			lastptr = tmp;
		}
		else lastptr = firstptr = tmp;
	}

	void pop()
	{
		chain<T>* tmp = firstptr;
		firstptr = firstptr->nextptr;
		delete tmp;
	}

	T front()
	{
		if (isempty()) throw - 1;
		return firstptr->value;
	}
};

