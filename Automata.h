#ifndef AUTOMATA
#define AUTOMATA

#include <vector>
#include <algorithm>
#include "RegExpr.h"

using namespace std;

template <typename T>
bool containsElement(const vector<T>& v, T el);
bool areTheSame(const vector<char>& alphabet1, const vector<char>& alphabet2);

struct Rule {
	Rule(size_t init, char letter, size_t dest) : init(init), letter(letter), dest(dest) {}
	size_t init;
	char letter;
	size_t dest;
	void print() {
		cout << init << " " << letter << " " << dest << endl;
	}
};
bool operator==(const Rule& lhs, const Rule& rhs);

class Automata {
private:
	size_t destinationDelta(size_t init, char letter) const;
	int existsEpsilonRule(size_t init) const;
	bool accepts(size_t tmpState, string word) const;
	bool acceptsEpsilon;
public:
	Automata static automataUnion(const Automata& left, const Automata& right);
	Automata static intersection(const Automata& left, const Automata& right);
	Automata static concat(const Automata& left, const Automata& right);
	Automata static complement(const Automata& automata);
	Automata static iteration(const Automata& automata);
	bool acceptsWord(string word);
	void print() const;

	size_t startState;
	size_t states;
	string regExpr;

	vector<char> alphabet;
	vector<bool> finalStates;
	vector<Rule> delta;
	vector<Rule> epsilons;
	Automata(const vector<char>& alphabet, size_t states, size_t startState, const vector<Rule>& delta, const vector<Rule>& epsilons, const vector<bool>& finalStates, bool acceptsEpsilon);
	Automata();
	Automata(const vector<char>& alphabet, char letter);

	//for testing
	void addRule(size_t init, char letter, size_t dest);

};
#endif