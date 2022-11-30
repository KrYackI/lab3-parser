#include <iostream>
#include <deque>
using namespace std;

//template<typename T> class Tqueue {
//	deque<T> pMem;
//public:
//	Tqueue() {};
//	bool isempty() { return pMem.empty(); }
//	bool isfull() { return pMem.size() == pMem.max_size(); }
//	int size() { return pMem.size(); }
//	void push(T obj)
//	{
//		if (isfull()) throw - 1;
//		pMem.push_back(obj);
//	}
//	void pop()
//	{
//		if (isempty()) throw - 1;
//		pMem.pop_front();
//	}
//	T front()
//	{
//		if (isempty()) throw - 1;
//		return pMem.front();
//	}
//};

//template<typename T> class Tqueue {
//	int size, start, end;
//	T* pMem;
//	int next(int i) { return (i + 1) % size; }
//public:
//	Tqueue() : size(2) { pMem = new T[2]; start = 0; end = next(start); };
//	Tqueue(const Tqueue& q) : size(q.size), end(q.end), start(q.start) { 
//		pMem = new T[size]; 
//		for (int i = end; i != start; i = next(i))
//			pMem[i] = q.pMem[i];
//		}
//	Tqueue& operator=(Tqueue& q){
//		if (this == &q) return *this;
//		size = q.size;
//		end = q.end;
//		start = q.start;
//		delete []pMem; 
//		pMem = new T[size];
//		for (int i = end; i != start; i = next(i))
//			pMem[i] = q.pMem[i];
//		return *this;
//	}
//	bool isempty() { return end == next(start); }
//	bool isfull() { return end == next(next(start)); }
//	void push(T obj)
//	{
//		if (isfull())
//		{
//			T* t;
//			T* tmp = new T[size * 2];
//			int j = 0;
//			for (int i = end; i != start; i = next(i))
//			{
//				tmp[j++] = pMem[i];
//				j++;
//			}
//			end = 0;
//			start = j;
//			size *= 2;
//			t = pMem;
//			pMem = tmp;
//			tmp = t;
//		}
//		start = next(start);
//		pMem[start] = obj;
//	}
//	void pop()
//	{
//		if (isempty()) throw - 1;
//		end = next(end);
//	}
//	//T last()
//	//{
//	//	if (isempty()) throw - 1;
//	//	return pMem[end];
//	//}
//	T front()
//	{
//		if (isempty()) throw - 1;
//		return pMem[end];
//	}
//	~Tqueue()
//	{
//		delete []pMem;
//	}
//};

template<typename T> class Tqueue {
	Tstack<T> left, right;
	size_t sz;
public:
	Tqueue() : sz(0) { };
	bool isempty() { return left.isempty() && right.isempty(); }
	bool isfull() { return left.isfull() && right.isfull(); }
	void push(T obj)
	{
		left.push(obj);
		sz++;
	}
	void pop()
	{
		if (isempty()) throw - 1;
		if (right.isempty())
		{
			while (!left.isempty())
				right.push(left.ppull());
		}
		right.pop();
		sz--;
	}
	//T last()
	//{
	//	if (isempty()) throw - 1;
	//	return pMem[end];
	//}
	T front()
	{
		if (isempty()) throw - 1;
		if (right.isempty())
		{
			while (!left.isempty())
				right.push(left.ppull());
		}
		return right.get();
	}
};

