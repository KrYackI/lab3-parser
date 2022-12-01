#include "synt.h"

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