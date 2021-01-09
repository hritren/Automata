#include "BST.hpp"
#include "Automata.h"


int main() {

	vector<char> alphabet = { 'a', 'b' };
	vector<Rule> delta1;
	vector<Rule> epsilons;
	vector<bool> final1 = { 1, 0 };
	vector<bool> final2 = { 0, 1, 0 };
	Automata a1(alphabet, 2, 0, delta1, epsilons, final1, true);
	a1.addRule(0, 'a', 0);
	a1.addRule(0, 'b', 1);
	a1.addRule(1, 'a', 1);
	a1.addRule(1, 'b', 1);

	Automata a2(alphabet, 3, 0, delta1, epsilons, final2, false);
	a2.addRule(0, 'a', 2);
	a2.addRule(0, 'b', 1);
	a2.addRule(1, 'a', 1);
	a2.addRule(1, 'b', 2);
	a2.addRule(2, 'a', 2);
	a2.addRule(2, 'b', 2);

	/*RegExpr* re = new BinaryOperator(new UnaryOperator(new Letter('a'), '*'), '+', new BinaryOperator(new Letter('b'), '.', new Letter('a')));
	re->print();*/
	Automata a3 = Automata::iteration(a2);
	cout << a3.acceptsWord("a") << endl;
	cout << a3.acceptsWord("b") << endl;
	cout << a3.acceptsWord("ba") << endl;
	cout << a3.acceptsWord("bb") << endl;
	cout << a2.acceptsWord("bb") << endl;
	cout << a2.acceptsWord("") << endl;
	cout << a3.acceptsWord("") << endl;

	return 0;
}