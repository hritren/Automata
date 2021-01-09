#include "Letter.h"

Letter::Letter(char letter) {
	if (letter == '*' || letter == '.' || letter == '+' || letter == '&') {
		throw "invalid letter";
	}
	this->letter = letter;
	type = LETTER;
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

Automata Letter::toAutomata() {
	return Automata(letter);
}
