#include "Automata.h"

bool contains(vector<char> alphabet, char letter) {
	for (size_t i = 0; i < alphabet.size(); i++) {
		if (alphabet[i] == letter) {
			return true;
		}
	}
	return false;
}


Automata::Automata() {
	states = 0;
	startState = UINT_MAX;
}

Automata::Automata(vector<char> alphabet, size_t states, size_t startState, vector<Edge> delta, vector<bool> finalStates) {
	this->alphabet = alphabet;
	this->states = states;
	this->startState = startState;
	this->delta = delta;
	this->finalStates = finalStates;
}

Automata Automata::complement(const Automata& automata) {
	vector<bool> resultFinalStates(automata.states);
	for (size_t i = 0; i < automata.finalStates.size(); i++) {
		if (!automata.finalStates[i]) {
			resultFinalStates[i] = true;
		}
	}
	return Automata(automata.alphabet, automata.states, automata.startState, automata.delta, resultFinalStates);
}

/*void Automata::addState(size_t state) {
	states.insert(state);
}

void Automata::addLetter(char letter) {
	alphabet.insert(letter);
}

void Automata::addFinalState(size_t finalState) {
	finalStates.insert(finalState);
}

void Automata::setStartState(size_t startState) {
	this->startState = startState;
}
*/
void Automata::addEdge(size_t init, char letter, size_t dest) {
	delta.push_back(Edge(init, letter, dest));
}

Automata Automata::automataUnion(const Automata& left, const Automata& right) {
	size_t states = left.states * right.states;

	size_t startState = left.startState * right.states + right.startState;

	vector<bool> finalStates(states);
	for (size_t i = 0; i < finalStates.size(); i++) {
		if (left.finalStates[i / right.states] || right.finalStates[i % right.states]) {
			finalStates[i] = true;
		}
	}

	vector<char> alphabet = left.alphabet;
	for (size_t i = 0; i < right.alphabet.size(); i++) {
		if (!contains(alphabet, right.alphabet[i])) {
			alphabet.push_back(right.alphabet[i]);
		}
	}

	vector<Edge> delta;
	for (size_t i = 0; i < states; i++) {
		for (size_t j = 0; j < alphabet.size(); j++) {
			size_t init = i;
			char letter = alphabet[j];
			size_t dest = left.destination(init / right.states, letter) * right.states + right.destination(init % right.states, letter);
			delta.push_back(Edge(init, letter, dest));
		}
	}
	return Automata(alphabet, states, startState, delta, finalStates);
}

size_t Automata::destination(size_t init, char letter) const {
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