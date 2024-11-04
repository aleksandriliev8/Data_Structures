#pragma once
#include "../src/Definitions.h"

struct DictionaryNode {
	bool isEndOfWord;
	int depth;
	char value;
	DictionaryNode* children[alphabetSize];

	//Constructor
	DictionaryNode() : isEndOfWord(false), depth(0), value('-') {

		//initializing all the children with nullptr
		for (size_t i = 0; i < alphabetSize; i++)
		{
			children[i] = nullptr;
		}
	}
};