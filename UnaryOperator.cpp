#include "UnaryOperator.h"

UnaryOperator::~UnaryOperator() {
	delete re;
}

UnaryOperator::UnaryOperator(RegExpr* re, char op,const vector<char>& alphabet) {
	if (op != '*') {
		throw "invalid operation";
	}
	if (!areTheSame(this->alphabet, re->getAlphabet())) {
		throw "the alphabets should be the same";
	}
	this->op = op;
	type = UNARY_OPERATOR;
	this->re = re;
	this->alphabet = alphabet;
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

Automata UnaryOperator::toAutomata() {
	return Automata::iteration(re->toAutomata());
}