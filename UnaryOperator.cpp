#include "UnaryOperator.h"

UnaryOperator::~UnaryOperator() {
	delete re;
}

UnaryOperator::UnaryOperator(RegExpr* re, char op) {
	if (op != '*') {
		throw "invalid operation";
	}
	this->op = op;
	type = 1;
	this->re = re;
}
std::string UnaryOperator::toString() {
	std::string result = "(" + re->toString();
	result += op;
	result += ")";
	return result;
}

void UnaryOperator::print() {
	std::cout << toString();
}