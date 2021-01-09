#include "Letter.h"

Letter::Letter(char letter) {
	if (letter == '*' || letter == '.' || letter == '+' || letter == '&') {
		throw "invalid letter";
	}
	this->letter = letter;
	type = 0;
}
std::string Letter::toString() {
	std::string result;
	result += '(';
	result += letter;
	result += ')';
	return result;
}

void Letter::print() {
	std::cout << toString();
}