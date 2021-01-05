#pragma once

#include <iostream>
#include <vector>
#include "BST.hpp"

using namespace std;
bool contains(vector<char> alphabet, char letter);
	struct Edge {
		Edge(size_t init, char letter, size_t dest) : init(init), letter(letter), dest(dest) {}
		size_t init;
		char letter;
		size_t dest;
		void print() {
			cout << init << " " << letter << " " << dest << endl;
		}
	};

class Automata {
private:
	size_t destination(size_t init, char letter) const;

public:
	size_t startState;
	size_t states;
	vector<char> alphabet;
	vector<Edge> delta;
	vector<bool> finalStates;
	Automata(vector<char> alphabet, size_t states, size_t startState, vector<Edge> delta, vector<bool> finalStates);
	Automata static complement(const Automata& automata);
	Automata();
	/*void addState(size_t state);
	void addFinalState(size_t finalState);
	void addLetter(char letter);
	void setStartState(size_t startState);*/
	void addEdge(size_t init, char letter, size_t dest);
	Automata static automataUnion(const Automata& left, const Automata& right);
	Automata static intersection(const Automata& left, const Automata& right);
};

