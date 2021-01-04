#include "Automata.h"

Automata::Automata() {
	startState = UINT_MAX;
}

Automata::Automata(BST<char> alphabet, BST<size_t> states, size_t startState, vector<Edge> delta, BST<size_t> finalStates) {
	this->alphabet = alphabet;
	this->states = states;
	this->startState = startState;
	this->delta = delta;
	this->finalStates = finalStates;
}

Automata Automata::complement() {
	BST<size_t> resultFinalStates = states;
	vector<size_t> finalStates = this->finalStates.toVector();
	for (size_t i = 0; i < finalStates.size(); i++) {
		if (resultFinalStates.contains(finalStates[i])) {
			resultFinalStates.remove(finalStates[i]);
		}
	}
	return Automata(alphabet, states, startState, delta, resultFinalStates);
}

void Automata::addState(size_t state) {
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

void Automata::addEdge(size_t init, char letter, size_t dest) {
	delta.push_back(Edge(init, letter, dest));
}