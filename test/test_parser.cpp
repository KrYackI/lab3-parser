#include "gtest.h"
#include "parser.h"

TEST(parser, erase)
{
	string str = "3 + ) 123 - 10( / 50 *	\t	30 \n";
	cout << str;
	str = delete_tr(str);
	cout << str;
	ASSERT_NO_THROW();
}

TEST(parser, rightbasic)
{
	string str = "3 + ( 110 -10)/ 50 *	\t	30 \n";
	cout << str;
	queue <Lexema> lex_res;
	LexAnalysis lexa(str);
	lex_res = lexa.lex(str);
	print(lex_res);
	SyntaxAnalysis s;
	cout << endl;
	print(s.rev(lex_res));
	Calculator c;
	EXPECT_EQ(c.calculate(s.rev(lex_res)), 63);
}

TEST(parser, syntexep1)
{
	string str = "3 + ) 123 -10(/ 50 *	\t	30 \n";
	cout << str;
	queue <Lexema> lex_res;
	LexAnalysis lexa(str);
	lex_res = lexa.lex(str);
	SyntaxAnalysis s;
	ASSERT_ANY_THROW(print(s.rev(lex_res)));
}
TEST(parser, syntexep2)
{
	string str = "3 + ( 123 - -10)/ 50 *	\t	30 \n";
	cout << str;
	queue <Lexema> lex_res;
	LexAnalysis lexa(str);
	lex_res = lexa.lex(str);
	SyntaxAnalysis s;
	ASSERT_ANY_THROW(print(s.rev(lex_res)));
}
TEST(parser, syntexep3)
{
	string str = "3 + ( (123 -10)/ 50 *	\t	30 \n";
	cout << str;
	queue <Lexema> lex_res;
	LexAnalysis lexa(str);
	lex_res = lexa.lex(str);
	SyntaxAnalysis s;
	ASSERT_ANY_THROW(print(s.rev(lex_res)));
}

TEST(parser, str_to_int)
{
	string str = "193";
	EXPECT_EQ(193, str_to_int(str));
}