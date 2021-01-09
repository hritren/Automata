#pragma once
#include "RegExpr.h"
class BinaryOperator : public RegExpr {
public:
	BinaryOperator(RegExpr* left, char op, RegExpr* right);
	~BinaryOperator();
	void print();
	std::string toString();
private:
	char op;
	RegExpr* left;
	RegExpr* right;
};

