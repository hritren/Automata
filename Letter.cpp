#include "Letter.h"

Letter::Letter(char letter, const vector<char>& alphabet) {
	if (!containsElement(alphabet, letter)) {
		throw "the letter should be in the alphabet";
	}
	if (letter == '*' || letter == '.' || letter == '+' || letter == '&') {
		throw "invalid letter";
	}
	this->letter = letter;
	type = LETTER;
	this->alphabet = alphabet;
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
	return Automata(alphabet, letter);
}
