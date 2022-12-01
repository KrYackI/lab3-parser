#include "calc.h"

class parser {
	LexAnalysis Lex;
	SyntaxAnalysis St;
	Calculator calc;
	string problem;
	queue<Lexema> straight_func;
	queue<Lexema> reverse_func;
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