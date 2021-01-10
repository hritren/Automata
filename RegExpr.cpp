#include "RegExpr.h"

size_t RegExpr::getType() { 
	return type;
}

vector<char> RegExpr::getAlphabet() {
	return alphabet;
}

RegExpr::~RegExpr() {}
