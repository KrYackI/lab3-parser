#include "lex.h"

//(123 + 10 * 2 - 1) / 20
//( - * * - - - * -) * - (* - - * * -)()()()
// -5 == (0 - 5)
// 6 - 5 == 6 + (0 - 5) 
//-5 = (0 - 5) = 0 5 -
//6 - 5 = 6 + (0 - 5) = 6 0 5 - +
//6 * (-5) = 6 * (0 - 5) = 6 0 5 - *

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
				throw exc("incorrect ')' operation before '(' in pos ", iter);
			}
		}
		iter++;
		while (!p.empty())
		{
			if (prev.getType() == p.front().getType()) // [op op] && [val val]
				if (prev.getStr() != "(" && prev.getStr() != ")" && p.front().getStr() != "(" && p.front().getStr() != ")")
				{
					throw exc("expected diff type of lexem in pos ", iter);
				}
			if (prev.getStr() == ")" && p.front().getType() == Value || p.front().getStr() == "(" && prev.getType() == Value) //[val (] && [)val]
			{
				throw exc("expected diff type of lexem in pos ", iter);
			}
			prev = p.front();
			p.pop();
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