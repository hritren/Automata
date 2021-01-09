#pragma once
#include"RegExpr.h"

class UnaryOperator : public RegExpr{
public:
	UnaryOperator(RegExpr* re, char op);
	~UnaryOperator();
	std::string toString();
	Automata toAutomata();
	void print();
private:
	RegExpr* re;
	char op;
};

