#include "Automata.h"

template <typename T>
bool containsElement(const vector<T>& v, T el) {
	for (size_t i = 0; i < v.size(); i++) {
		if (v[i] == el) {
			return true;
		}
	}
	return false;
}

bool operator==(const Rule& lhs, const Rule& rhs) {
	return lhs.init == rhs.init && lhs.letter == rhs.letter && lhs.dest == rhs.dest;
}

bool areTheSame(const vector<char>& alphabet1, const vector<char>& alphabet2) {
	if (alphabet1.size() != alphabet2.size()) {
		return false;
	}
	sort(alphabet1.begin(), alphabet1.end());
	sort(alphabet2.begin(), alphabet2.end());
	for (size_t i = 0; i < alphabet1.size(); i++) {
		if (alphabet1[i] != alphabet2[i]) {
			return false;
		}
	}
	return true;
}

Automata::Automata() {
	states = 0;
	startState = UINT_MAX;
	acceptsEpsilon = false;
}

Automata::Automata(const vector<char>& alphabet, size_t states, size_t startState, const vector<Rule>& delta, const vector<Rule>& epsilons, const vector<bool>& finalStates, bool acceptsEpsilon) {
	this->alphabet = alphabet;
	this->states = states;
	this->startState = startState;
	this->delta = delta;
	this->finalStates = finalStates;
	this->epsilons = epsilons;
	this->acceptsEpsilon = acceptsEpsilon;
}

Automata Automata::complement(const Automata& automata) {
	vector<bool> resultFinalStates(automata.states);
	for (size_t i = 0; i < automata.finalStates.size(); i++) {
		if (!automata.finalStates[i]) {
			resultFinalStates[i] = true;
		}
	}
	return Automata(automata.alphabet, automata.states, automata.startState, automata.delta, automata.epsilons, resultFinalStates, !automata.acceptsEpsilon);
}

void Automata::addRule(size_t init, char letter, size_t dest) {
	delta.push_back(Rule(init, letter, dest));
}

Automata Automata::automataUnion(const Automata& left, const Automata& right) {
	if (!areTheSame(left.alphabet, right.alphabet)) {
		throw "the alphabets should be the same";
	}
	vector<char> alphabet = left.alphabet;

	size_t states = left.states * right.states;

	size_t startState = left.startState * right.states + right.startState;

	vector<bool> finalStates(states);
	for (size_t i = 0; i < finalStates.size(); i++) {
		if (left.finalStates[i / right.states] || right.finalStates[i % right.states]) {
			finalStates[i] = true;
		}
	}

	vector<Rule> delta;
	for (size_t i = 0; i < states; i++) {
		for (size_t j = 0; j < alphabet.size(); j++) {
			size_t init = i;
			char letter = alphabet[j];
			size_t dest = left.destinationDelta(init / right.states, letter) * right.states + right.destinationDelta(init % right.states, letter);
			delta.push_back(Rule(init, letter, dest));
		}
	}

	vector<Rule> epsilons = left.epsilons;
	for (size_t i = 0; i < right.epsilons.size(); i++) {
		Rule epsilonRule = right.epsilons[i];
		epsilonRule.init += left.states;
		epsilons.push_back(epsilonRule);
	}
	return Automata(alphabet, states, startState, delta, epsilons, finalStates, left.acceptsEpsilon || right.acceptsEpsilon);
}

size_t Automata::destinationDelta(size_t init, char letter) const {
	for (size_t i = 0; i < delta.size(); i++) {
		if (delta[i].init == init && delta[i].letter == letter) {
			return delta[i].dest;
		}
	}
	throw "Invalid init state or letter";
}

Automata Automata::intersection(const Automata& left, const Automata& right) {
	return complement(automataUnion(complement(left), complement(right)));
}

bool Automata::accepts(size_t tmpState, string word) const {
	if (word.empty()) {
		return acceptsEpsilon;
	}
	for (size_t i = 0; i < word.size(); i++) {
		int epsilonResullt = existsEpsilonRule(tmpState);
		if (epsilonResullt != -1) {
			if (accepts(epsilonResullt, word.substr(i, word.size() - i))) {
				return true;
			}
		}
		tmpState = destinationDelta(tmpState, word[i]);
	}
	int epsilonResullt = existsEpsilonRule(tmpState);
	if (epsilonResullt != -1) {
		if (finalStates[epsilonResullt]) {
			return true;
		}
	}
	if (finalStates[tmpState]) {
		return true;
	}
	return false;
}

void Automata::print() const {
	cout << "alphabet: ";
	for (size_t i = 0; i < alphabet.size(); i++) {
		cout << alphabet[i] << " ";
	}

	cout << endl << "set of states: {";
	bool firstIteration = true;
	for (size_t i = 0; i < states; i++) {
		if (firstIteration) {
			cout << "q" << i;
			firstIteration = false;
		} else {
			cout << ", q" << i;
		}
	}

	cout << "}";
	cout << endl << "q(start) = q" << startState << endl;

	cout << "delta: ";
	for (size_t i = 0; i < delta.size(); i++) {
		cout << endl << "(q" << delta[i].init << ", " << delta[i].letter << ") -> q" << delta[i].dest;
	}
	for (size_t i = 0; i < epsilons.size(); i++) {
		cout << endl << "(q" << epsilons[i].init << ", " << epsilons[i].letter << ") -> q" << epsilons[i].dest;
	}
	cout << endl << "set of final states: {";
	firstIteration = true;
	for (size_t i = 0; i < states; i++) {
		if (finalStates[i]) {
			if (firstIteration) {
				cout << "q" << i;
				firstIteration = false;
			} else {
				cout << ", q" << i;
			}
		}
	}
	cout << "}" << endl;
}

Automata Automata::concat(const Automata& left, const Automata& right) {
	vector<char> alphabet(left.alphabet);
	for (size_t i = 0; i < right.alphabet.size(); i++) {
		if (!containsElement(alphabet, right.alphabet[i])) {
			alphabet.push_back(right.alphabet[i]);
		}
	}

	size_t states = left.states + right.states;

	size_t startState = left.startState;

	vector<Rule> delta = left.delta;
	for (size_t i = 0; i < right.delta.size(); i++) {
		Rule rule = right.delta[i];
		rule.init += left.states;
		rule.dest += left.states;
		delta.push_back(rule);
	}

	vector<Rule> epsilons = left.epsilons;

	for (size_t i = 0; i < right.epsilons.size(); i++) {
		Rule epsRule = right.epsilons[i];
		epsRule.init += left.states;
		epsRule.dest += left.states;
		epsilons.push_back(epsRule);
	}

	vector<bool> finalStates(states);
	if (right.finalStates[startState]) {
		for (size_t i = 0; i < left.finalStates.size(); i++) {
			finalStates[i] = left.finalStates[i];
		}
	}

	for (size_t i = 0; i < right.finalStates.size(); i++) {
		finalStates[left.finalStates.size() + i] = right.finalStates[i];
	}
	return Automata(alphabet, states, startState, delta, epsilons, finalStates, left.acceptsEpsilon && right.acceptsEpsilon);
}

int Automata::existsEpsilonRule(size_t init) const {
	for (size_t i = 0; i < epsilons.size(); i++) {
		if (epsilons[i].init == init) {
			return epsilons[i].dest;
		}
	}
	return -1;
}

bool Automata::acceptsWord(string word) {
	return accepts(startState, word);
}

Automata Automata::iteration(const Automata& automata) {
	vector<bool> finalStates = automata.finalStates;

	vector<Rule> epsilons = automata.epsilons;
	for (size_t i = 0; i < finalStates.size(); i++) {
		if (finalStates[i]) {
			Rule epsRule = Rule(i, '@', automata.startState);
			if (!containsElement(epsilons, epsRule)) {
			epsilons.push_back(epsRule);
			}
		}
	}

	return Automata(automata.alphabet, automata.states, automata.startState, automata.delta, epsilons, finalStates, true);
}

Automata::Automata(const vector<char>& alphabet, char letter) {
	this->alphabet = alphabet;

	acceptsEpsilon = false;

	states = 3;

	startState = 0;

	finalStates.resize(states);
	finalStates[1] = true;

	delta.push_back(Rule(0, letter, 1));
	delta.push_back(Rule(1, letter, 2));
	delta.push_back(Rule(2, letter, 2));

	for (size_t i = 0; i < alphabet.size(); i++) {
		if (alphabet[i] == letter) {
			continue;
		}
		Rule tmpRule = Rule(0, alphabet[i], 2);
		delta.push_back(tmpRule);
		tmpRule = Rule(1, alphabet[i], 2);
		delta.push_back(tmpRule);
		tmpRule = Rule(2, alphabet[i], 2);
		delta.push_back(tmpRule);
	}
}
