#pragma once

class Statistics {
private:
	unsigned int correct;
	unsigned int incorrect;
public:
	Statistics();
	Statistics(unsigned int, unsigned int);
	~Statistics();

	void setCorrect(unsigned int);
	void setIncorrect(unsigned int);

	unsigned int getCorrect() const;
	unsigned int getIncorrect() const;

	void increaseCorrect();
	void increaseIncorrect();
	
	void print() const;
};