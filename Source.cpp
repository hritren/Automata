#pragma once

#include "Automata.h"
#include "BinaryOperator.h"
#include "UnaryOperator.h"
#include "Letter.h"
#include <fstream>

int main() {
	vector<char> alphabet = { 'a', 'b' };
	RegExpr* re = new BinaryOperator(new Letter('a', alphabet), '+', new Letter('b', alphabet), alphabet);
	Automata a3 = Automata::fromRegExpr(re);
	ifstream iFile("words.txt", ios::in);
	string word;
	while (iFile >> word) {
		cout << a3.acceptsWord(word) << endl;
	}
	iFile.close();
	delete re;
	return 0;
}