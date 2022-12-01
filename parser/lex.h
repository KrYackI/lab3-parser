#include <string>
#include <iostream>
#include "stack.h" // сделать свой
#include "queue.h" // сделать свой
//вместо switch можно сделать список(массив) правил
//базовый класс rool, три метода: перейти, чек и действие
//сделать отдельными классами лексический, синтаксический анализы и транслятор

#define queue Tqueue
#ifdef queue
#define empty isempty

#endif

#define stack Tstack

using namespace std;

enum TypeElement {
	Operation,
	Value
};

enum TTypeElement {
	NAE,
	Unary,
	Binary,
	Valuee
};

class Lexema {
	string str;
	TypeElement type;
	int pos;
public:
	Lexema(string _str = " ", TypeElement _type = Value, int _pos = 0) : str(_str), type(_type), pos(_pos) {};
	string getStr() { return str; }
	TypeElement getType() { return type; }
	int getpos() { return pos; }
	int priority()
	{
		//if (type == Unary) return 4;
		string op = "()+-*/";
		return op.find(str) / 2;
	}
	friend ostream& operator << (ostream& out, Lexema& p) {
		out << "{" << p.str << ", ";
		if (p.type == Operation) {
			out << "operation";
		}
		else if (p.type == Value) {
			out << "value";
		};
		out << "}";
		return out;
	}
	~Lexema() {}
};

//class Lexema_V : public Lexema {
//	string str;
//	TypeElement type;
//public:
//	Lexema_V(string _str = " ") : Lexema(_str, Value) {};
//};

//queue <Lexema> lex(string input) {
//	queue<Lexema>res;
//	input += ' ';
//	int i = 0;
//	string tmp = "";
//	string op = "+-*/()";
//	string sep = " \n\t";
//	int state = 0;
//	for (i = 0; i < input.size(); i++) {
//		char c = input[i];
//		int fres;
//		switch (state)
//		{
//		case 0: // операция
//			if (c >= '0' && c <= '9') {
//				tmp = c;
//				state = 1;
//				break;
//			}
//			fres = op.find(c);
//			if (fres >= 0) {
//				tmp = c;
//				Lexema l(tmp, Operation);
//				res.push(l);
//				state = 0;
//				break;
//			}
//			break;
//		case 1: // число
//			if (c >= '0' && c <= '9') {
//				tmp += c;
//				state = 1;
//				break;
//			}
//			fres = op.find(c);
//			if (fres >= 0) {
//				Lexema l1(tmp, Value);
//				res.push(l1);
//				tmp = c;
//				Lexema l2(tmp, Operation);
//				res.push(l2);
//				state = 0;
//				break;
//			}
//			fres = sep.find(c);
//			if (fres >= 0) {
//				Lexema l(tmp, Value);
//				res.push(l);
//				state = 0;
//				break;
//			}
//			break;
//		}
//	}
//	return res;
//}

void print(queue <Lexema> t) {
	while (!t.empty()) {
		cout << t.front() << endl;
		t.pop();
	}
	cout << endl;
}

string delete_tr(string s)
{
	string sep = " \n\t";
	char c;
	int fres;
	for (int i = 0; i < s.size(); i++)
	{
		c = s[i];
		fres = sep.find(c);
		if (fres >= 0)
		{
			int l = i;
			for (; i < s.size() && fres >= 0; i++, fres = sep.find(s[i])) {}
			s.erase(l, i - l - 1);
			i = l;
		}
	}
	return s;
}

class LexAnalysis {
	queue<Lexema> problem;
public:
	queue <Lexema> lex(string input)
	{
		//input = delete_tr(input);
		queue<Lexema>res;
		input += ' ';
		int i = 0;
		string tmp = "";
		string op = "+-*/()";
		string sep = " \n\t";
		int state = 0;
		for (i = 0; i < input.size(); i++) {
			char c = input[i];
			int fres;
			switch (state)
			{
			case 0: // операция
				if (c >= '0' && c <= '9') {
					tmp = c;
					state = 1;
					break;
				}
				fres = op.find(c);
				if (fres >= 0) {
					tmp = c;
					Lexema l(tmp, Operation);
					res.push(l);
					state = 0;
					break;
				}
				break;
			case 1: // число
				if (c >= '0' && c <= '9') {
					tmp += c;
					state = 1;
					break;
				}
				fres = op.find(c);
				if (fres >= 0) {
					Lexema l1(tmp, Value);
					res.push(l1);
					tmp = c;
					Lexema l2(tmp, Operation);
					res.push(l2);
					state = 0;
					break;
				}
				fres = sep.find(c);
				if (fres >= 0) {
					Lexema l(tmp, Value);
					res.push(l);
					state = 0;
					break;
				}
				break;
			}
		}
		return res;
	}

	LexAnalysis(string s = "") : problem(lex(s)) {};
	queue<Lexema>& getproblem() { return problem; }
};