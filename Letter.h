#pragma once
#include "RegExpr.h"

class Letter : public RegExpr {
public:
	Letter(char letter, const vector<char>& alphabet);
	void print();
	std::string toString();
	Automata toAutomata();
private:
	char letter;
};

