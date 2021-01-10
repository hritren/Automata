#pragma once
#include "RegExpr.h"
class BinaryOperator : public RegExpr {
public:
	BinaryOperator(RegExpr* left, char op, RegExpr* right, const vector<char>& alphabet);
	~BinaryOperator();
	void print();
	std::string toString();
	Automata toAutomata();
private:
	char op;
	RegExpr* left;
	RegExpr* right;
};

