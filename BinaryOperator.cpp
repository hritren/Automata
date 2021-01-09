#include "BinaryOperator.h"

BinaryOperator::BinaryOperator(RegExpr* left, char op, RegExpr* right) {
	if (op != '+' && op != '.' && op != '&') {
		throw "invalid operation";
	}
	this->op = op;
	this->left = left;
	this->right = right;
	type = 2;
}

BinaryOperator::~BinaryOperator() {
	delete left;
	delete right;
}

void BinaryOperator::print() {
	std::cout << toString();
}

std::string BinaryOperator::toString() {
	std::string result = "(" + left->toString() + " ";
	result += op;
	result += " " + right->toString() + ")";
	return result;
}