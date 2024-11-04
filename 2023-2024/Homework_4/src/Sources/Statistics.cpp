#include <iostream>
#include "../src/Statistics.h"

Statistics::Statistics() {
	correct = 0;
	incorrect = 0;
}

Statistics::Statistics(unsigned int _correct, unsigned int _incorrect) {
	setCorrect(_correct);
	setIncorrect(_incorrect);
}

Statistics::~Statistics() {
	correct = 0;
	incorrect = 0;
}

void Statistics::setCorrect(unsigned int _correct) {
	correct = _correct;
}

void Statistics::setIncorrect(unsigned int _incorrect) {
	incorrect = _incorrect;
}

unsigned int Statistics::getCorrect() const {
	return correct;
}

unsigned int Statistics::getIncorrect() const {
	return incorrect;
}

void Statistics::increaseCorrect() {
	++correct;
}

void Statistics::increaseIncorrect() {
	++incorrect;
}

void Statistics::print() const {
	std::cout << correct << " correct, " << incorrect << " incorrect" << std::endl;
}