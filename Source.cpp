#pragma once

#include "Automata.h"
#include "BinaryOperator.h"
#include "UnaryOperator.h"
#include "Letter.h"

int main() {

	vector<char> al = { 'a', 'b' };
	vector<Rule> delta1;
	vector<Rule> epsilons;
	vector<bool> final1 = { 1, 0 };
	vector<bool> final2 = { 0, 1, 0 };
	Automata a1(al, 2, 0, delta1, epsilons, final1, true);
	a1.addRule(0, 'a', 0);
	a1.addRule(0, 'b', 1);
	a1.addRule(1, 'a', 1);
	a1.addRule(1, 'b', 1);

	Automata a2(al, 3, 0, delta1, epsilons, final2, false);
	a2.addRule(0, 'a', 2);
	a2.addRule(0, 'b', 1);
	a2.addRule(1, 'a', 1);
	a2.addRule(1, 'b', 2);
	a2.addRule(2, 'a', 2);
	a2.addRule(2, 'b', 2);

	RegExpr* re = new BinaryOperator(new Letter('a', al), '+', new Letter('b', al), al);
	Automata a3 = re->toAutomata();
	a3.print();
	delete re;
	return 0;
}