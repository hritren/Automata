#include "BST.hpp"
#include "Automata.h"


int main() {

	vector<char> alphabet = { 'a', 'b' };
	vector<Edge> delta1;
	vector<bool> final1 = { 1, 0 };
	vector<bool> final2 = { 0, 1, 0 };
	Automata a1(alphabet, 2, 0, delta1, final1);
	a1.addEdge(0, 'a', 0);
	a1.addEdge(0, 'b', 1);
	a1.addEdge(1, 'a', 1);
	a1.addEdge(1, 'b', 1);

	Automata a2(alphabet, 3, 0, delta1, final2);
	a2.addEdge(0, 'a', 2);
	a2.addEdge(0, 'b', 1);
	a2.addEdge(1, 'a', 1);
	a2.addEdge(1, 'b', 2);
	a2.addEdge(2, 'a', 2);
	a2.addEdge(2, 'b', 2);

	Automata united = Automata::automataUnion(a1, a2);
	cout << united.startState << " " << united.states << endl;
	alphabet = united.alphabet;
	delta1 = united.delta;
	final1 = united.finalStates;

	for (size_t i = 0; i < alphabet.size(); i++) {
		cout << alphabet[i];
	}
	cout << endl;
	for (size_t i = 0; i < delta1.size(); i++) {
		delta1[i].print();
	}
	for (size_t i = 0; i < final1.size(); i++) {
		cout << final1[i] << " ";
	}

	cout << endl;
	cout << endl;
	Automata intersected = Automata::intersection(a1, a2);

	cout << intersected.startState << " " << intersected.states << endl;
	alphabet = intersected.alphabet;
	delta1 = intersected.delta;
	final1 = intersected.finalStates;

	for (size_t i = 0; i < alphabet.size(); i++) {
		cout << alphabet[i];
	}
	cout << endl;
	for (size_t i = 0; i < delta1.size(); i++) {
		delta1[i].print();
	}
	for (size_t i = 0; i < final1.size(); i++) {
		cout << final1[i] << " ";
	}
	return 0;
}