#pragma once
#include"RegExpr.h"
class UnaryOperator : public RegExpr{
public:
	UnaryOperator(RegExpr* re, char op);
	~UnaryOperator();
	std::string toString();
	void print();
private:
	RegExpr* re;
	char op;
};

