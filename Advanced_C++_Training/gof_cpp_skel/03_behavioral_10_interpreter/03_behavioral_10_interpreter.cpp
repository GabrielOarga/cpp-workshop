#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

enum TokenType
{
	INTEGER, PLUS, _EOF
};

class Token  // terminal
{
public:
	Token(TokenType type, char value) : m_type(type), m_value(value) {}
	Token() {}
	TokenType getType() const { return m_type; }
	char getValue() const { return m_value; }

private:
	TokenType m_type;
	char m_value;
};


class SimpleInterpreter
{
public:
	SimpleInterpreter(string& expression) : m_text(expression) {}

//	Token getNextToken()
//	{

//	}

	void consume(TokenType type)
	{
//		if (m_currentToken.getType() == type) {
//			m_currentToken = getNextToken();
//		} else {
//			throw string{ "Cannot parse expression" };
//		}
	}

	int calculateExression()
	{
	}

private:
	Token m_currentToken{};
	string m_text{};
	int m_pos{};

};


int main()
{
	string expr;
	while (true) {
		cout << "Expr: ";
		cin >> expr;
		if (expr == "q")
			break;
		try {
			int result = SimpleInterpreter{ expr }.calculateExression();
			cout << result << endl;
		} catch (string& e) {
			cout << e << endl;
		}
	}

	getchar();
	return 0;
}
