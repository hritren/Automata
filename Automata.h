#pragma once

#include <iostream>
#include <vector>
#include "BST.hpp"

using namespace std;
	struct Edge {
		Edge(size_t init, char letter, size_t dest) : init(init), letter(letter), dest(dest) {}
		size_t init;
		char letter;
		size_t dest;
	};
class Automata {
private:
	size_t startState;
	BST<size_t> states;
	BST<char> alphabet;
	vector<Edge> delta;
	BST<size_t> finalStates;
	Automata(BST<char> alphabet, BST<size_t> states, size_t startState, vector<Edge> delta, BST<size_t> finalStates);

public:
	Automata complement();
	Automata();
	void addState(size_t state);
	void addFinalState(size_t finalState);
	void addLetter(char letter);
	void setStartState(size_t startState);
	void addEdge(size_t init, char letter, size_t dest);
};

