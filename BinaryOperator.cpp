#include "BinaryOperator.h"

BinaryOperator::BinaryOperator(RegExpr* left, char op, RegExpr* right, const vector<char>& alphabet) {
	if (op != '+' && op != '.' && op != '&') {
		throw "invalid operation";
	}
	if (!areTheSame(left->getAlphabet(), right->getAlphabet()) || !areTheSame(alphabet, left->getAlphabet())) {
		throw "the alphabets should be the same";
	}
	this->alphabet = alphabet;
	this->op = op;
	this->left = left;
	this->right = right;
	type = BINARY_OPERATOR;
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

Automata BinaryOperator::toAutomata() {
	if (op == '+') {
		return Automata::automataUnion(left->toAutomata(), right->toAutomata());
	}

	if (op == '.') {
		return Automata::concat(left->toAutomata(), right->toAutomata());
	}

	if (op == '&') {
		return Automata::intersection(left->toAutomata(), right->toAutomata());
	}

	throw "invalid operation";
}