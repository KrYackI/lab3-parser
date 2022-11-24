#include <string>
#include <iostream>
#include "stack.h" // сделать свой
#include "queue.h" // сделать свой
#include <queue>
//вместо switch можно сделать список(массив) правил
//базовый класс rool, три метода: перейти, чек и действие
//сделать отдельными классами лексический, синтаксический анализы и транслятор

//#define queue Tqueue
#define stack Tstack

using namespace std;

enum TypeElement {
	Operation,
	Value
};

class Lexema {
	string str;
	TypeElement type;
public:
	Lexema(string _str = " ", TypeElement _type = Value) : str(_str), type(_type) {};
	string getStr() { return str; }
	TypeElement getType() { return type; }
	int priority()
	{
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
};

queue <Lexema> lex(string input) {
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

void print(queue <Lexema> t) {
	while (!t.empty()) {
		cout << t.front() << endl;
		t.pop();
	}
	cout << endl;
}

class LexAnalysis {
	queue<Lexema> problem;
	queue <Lexema> lex(string input) 
	{
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
public:
	LexAnalysis(string s) : problem(lex(s)) {};
	queue<Lexema> getproblem() { return problem; }
};

//(123 + 10 * 2 - 1) / 20
//( - * * - - - * -) * - (* - - * * -)()()()

class exc {
	string str;
	int index;
public:
	exc(string s, int i) : str(s), index(i) {}
	friend ostream& operator<<(ostream& out, exc e)
	{
		out << e.str << e.index << endl;
		return out;
	}
};

class SyntaxAnalysis {

	void CorrectCheck(queue<Lexema> p) {
		int flag = 0;
		int iter = 1;
		Lexema prev = p.front();
		p.pop();
		if (prev.getStr() == "(") flag++;
		if (prev.getStr() == ")")
		{
			flag--;
			if (flag < 0) 
			{
				throw new exc("incorrect ')' operation before '(' in pos ", iter);
			}
		}
		iter++;
		while (!p.empty())
		{
			if (prev.getType() == p.front().getType()) 
				if (prev.getStr() != "(" && prev.getStr() != ")" && p.front().getStr() != "(" && p.front().getStr() != ")")
				{
				throw new exc("expected diff type of lexem in pos ", iter);
				}
			prev = p.front();
			p.pop();
			if (prev.getStr() == "(") flag++;
			if (prev.getStr() == ")")
			{
				flag--;
				if (flag < 0)
				{
					throw new exc("incorrect ')' operation before '(' in pos ", iter);
				}
			}
			iter++;
		}
		if (flag) 
		{
			throw new exc("number of ')' not equal to ')' ", -1);
		}
	}

public:
	SyntaxAnalysis() {};
	queue<Lexema> rev(queue<Lexema> clone)
	{
		try { CorrectCheck(clone); }
		catch (exc e) { cout << e; throw - 1; }

		queue<Lexema> reverse;
		stack<Lexema> st;
		while (!clone.empty())
		{
			if (clone.front().getType() == Value)
			{
				reverse.push(clone.front());
			}
			if (clone.front().getType() == Operation)
			{
				if (clone.front().getStr() == "(") st.push(clone.front());
				else if (clone.front().getStr() == ")") 
				{
					while (st.get().priority() != clone.front().priority())
						reverse.push(st.ppull());
					st.pop();
				}
				else 
				{
					while ((!st.isempty()) && (st.get().priority() >= clone.front().priority()))
					{
						reverse.push(st.ppull());
					}
					st.push(clone.front());
				}
			}
			clone.pop();
		}
		while (!st.isempty())
			reverse.push(st.ppull());
		return reverse;
	}
};

int str_to_int(string s)
{
	int res = 0;
	for (int i = 0; i < s.length(); i++)
		res = res * 10 + s[i] - '0';
	return res;
}

class calculator
{
public:
	calculator() {};
	int calculate(queue<Lexema> p)
	{
		stack<int> st;
		while (!p.empty())
		{
			if (p.front().getType() == Value)
				st.push(str_to_int(p.front().getStr()));
			if (p.front().getType() == Operation)
			{
				int r = st.ppull();
				int l = st.ppull();
				switch (p.front().getStr()[0])
				{
				case '+': st.push(l + r);
					break;
				case '-': st.push(l - r);
					break;
				case '*': st.push(l * r);
					break;
				case '/': if (r == 0) throw "divider is 0";
					st.push(l / r);
					break;
				}
			}
			p.pop();
		}
		return st.get();
	}
};