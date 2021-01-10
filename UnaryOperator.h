#pragma once
#include"RegExpr.h"

class UnaryOperator : public RegExpr{
public:
	UnaryOperator(RegExpr* re, char op, const vector<char>& alphabet);
	~UnaryOperator();
	std::string toString();
	Automata toAutomata();
	void print();
private:
	RegExpr* re;
	char op;
};

