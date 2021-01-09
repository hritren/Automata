#pragma once
#include "RegExpr.h"
class Letter : public RegExpr {
public:
	Letter(char letter);
	void print();
	std::string toString();
private:
	char letter;
};

