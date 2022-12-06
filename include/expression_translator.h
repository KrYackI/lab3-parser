
#include <string>
#include <iostream>
#include "Stack.h" 
#include <Queue>
#include <Stack>

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
	~Lexema() {}
};

Queue <Lexema> lex(string input) {
	Queue<Lexema>res;
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
		case 0: 
			if (c >= '0' && c <= '9') {
				tmp = c;
				state = 1;
				break;
			}
			fres = op.find(c);
			if (fres >= 0) {
				tmp = c;
				Lexema l(tmp, Operation);
				res.Push(l);
				state = 0;
				break;
			}
			break;
		case 1: 
			if (c >= '0' && c <= '9') {
				tmp += c;
				state = 1;
				break;
			}
			fres = op.find(c);
			if (fres >= 0) {
				Lexema l1(tmp, Value);
				res.Push(l1);
				tmp = c;
				Lexema l2(tmp, Operation);
				res.Push(l2);
				state = 0;
				break;
			}
			fres = sep.find(c);
			if (fres >= 0) {
				Lexema l(tmp, Value);
				res.Push(l);
				state = 0;
				break;
			}
			break;
		}
	}
	return res;
}

void print(Queue <Lexema> t) {
	while (!t.IsEmpty()) {
		cout << t.Top() << endl;
		t.Pop();
	}
	cout << endl;
}

class LexAnalysis {
	Queue<Lexema> problem;
public:
	Queue <Lexema> lex(string input)
	{
		Queue<Lexema>res;
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
			case 0: 
				if (c >= '0' && c <= '9') {
					tmp = c;
					state = 1;
					break;
				}
				fres = op.find(c);
				if (fres >= 0) {
					tmp = c;
					Lexema l(tmp, Operation);
					res.Push(l);
					state = 0;
					break;
				}
				break;
			case 1: 
				if (c >= '0' && c <= '9') {
					tmp += c;
					state = 1;
					break;
				}
				fres = op.find(c);
				if (fres >= 0) {
					Lexema l1(tmp, Value);
					res.Push(l1);
					tmp = c;
					Lexema l2(tmp, Operation);
					res.Push(l2);
					state = 0;
					break;
				}
				fres = sep.find(c);
				if (fres >= 0) {
					Lexema l(tmp, Value);
					res.Push(l);
					state = 0;
					break;
				}
				break;
			}
		}
		return res;
	}

	LexAnalysis(string s = "") : problem(lex(s)) {};
	Queue<Lexema>& getproblem() { return problem; }
};



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

	void CorrectCheck(Queue<Lexema> p) {
		int flag = 0;
		int iter = 1;
		Lexema prev = p.Top();
		p.Pop();
		if (prev.getStr() == "(") flag++;
		if (prev.getStr() == ")")
		{
			flag--;
			if (flag < 0)
			{
				throw exc("incorrect ')' operation before '(' in pos ", iter);
			}
		}
		iter++;
		while (!p.IsEmpty())
		{
			if (prev.getType() == p.Top().getType())
				if (prev.getStr() != "(" && prev.getStr() != ")" && p.Top().getStr() != "(" && p.Top().getStr() != ")")
				{
					throw exc("expected diff type of lexem in pos ", iter);
				}
			prev = p.Top();
			p.Pop();
			if (prev.getStr() == "(") flag++;
			if (prev.getStr() == ")")
			{
				flag--;
				if (flag < 0)
				{
					throw exc("incorrect ')' operation before '(' in pos ", iter);
				}
			}
			iter++;
		}
		if (flag)
		{
			throw exc("number of ')' not equal to ')' ", -1);
		}
	}

public:
	SyntaxAnalysis() {};
	Queue<Lexema> rev(Queue<Lexema> clone)
	{
		try { CorrectCheck(clone); }
		catch (exc e) { cout << e; throw - 1; }

		Queue<Lexema> reverse;
		Stack<Lexema> st;
		while (!clone.IsEmpty())
		{
			if (clone.Top().getType() == Value)
			{
				reverse.Push(clone.Top());
			}
			if (clone.Top().getType() == Operation)
			{
				if (clone.Top().getStr() == "(") st.Push(clone.Top());
				else if (clone.Top().getStr() == ")")
				{
					while (st.Top().priority() != clone.Top().priority())
						reverse.Push(st.Pop());
					st.Pop();
				}
				else
				{
					while ((!st.IsEmpty()) && (st.Top().priority() >= clone.Top().priority()))
					{
						reverse.Push(st.Pop());
					}
					st.Push(clone.Top());
				}
			}
			clone.Pop();
		}
		while (!st.IsEmpty())
			reverse.Push(st.Pop());
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

class Calculator
{
public:
	Calculator() {};
	int calculate(Queue<Lexema> p)
	{
		Stack<int> st;
		while (!p.IsEmpty())
		{
			if (p.Top().getType() == Value)
				st.Push(str_to_int(p.Top().getStr()));
			if (p.Top().getType() == Operation)
			{
				int r = st.Pop();
				int l = st.Pop();
				switch (p.Top().getStr()[0])
				{
				case '+': st.Push(l + r);
					break;
				case '-': st.Push(l - r);
					break;
				case '*': st.Push(l * r);
					break;
				case '/': if (r == 0) throw "divider is 0";
					st.Push(l / r);
					break;
				}
			}
			p.Pop();
		}
		return st.Top();
	}
};

class parser {
	LexAnalysis Lex;
	SyntaxAnalysis St;
	Calculator calc;
	string problem;
	Queue<Lexema> straight_func;
	Queue<Lexema> reverse_func;
	int answer;
public:
	parser(string s = "") : problem(s), answer(NAN) {};
	void setProblem(string s) { problem = s; }
	void calculate_all()
	{
		straight_func = Lex.lex(problem);
		reverse_func = St.rev(straight_func);
		answer = calc.calculate(reverse_func);
	}
	string getProblem() { return problem; }
	int getAnswer() { if (answer == NAN) calculate_all(); return answer; }

};