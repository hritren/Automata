#pragma once
#include<iostream>
#include "Automata.h"

const size_t LETTER = 0;
const size_t UNARY_OPERATOR = 1;
const size_t BINARY_OPERATOR = 2;

class RegExpr {
public:
	virtual void print() = 0;
	virtual std::string toString() = 0;
	virtual ~RegExpr();
	virtual Automata toAutomata() = 0;
	size_t getType();
protected:
	size_t type;
};

