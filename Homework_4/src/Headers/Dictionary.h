#pragma once

#include <stdexcept>
#include <unordered_set>
#include "../src/DictionaryNode.h"

class incorrect_word_exception : public std::runtime_error {
public:
  incorrect_word_exception()
    : runtime_error("incorrect word")
  {
    // Nothing to do here
  }
};

#define alphabetSize 26

class Dictionary {
public:
	Dictionary() {
		root = new DictionaryNode();
		sizeDictionary = 0;
	}

	~Dictionary() {
		clear(root);
		sizeDictionary = 0;
	};

	void insert(const char* word);
	void erase(const char* word) noexcept;
	bool contains(const char* word) const noexcept;
	size_t size() const noexcept;
	static bool isCorrectWord(const char* word) noexcept;

private:

	//TODO: Add your implementation details
  
	size_t sizeDictionary;
    DictionaryNode* root;

    void clear(DictionaryNode* root);
	bool isEmpty(DictionaryNode* root);
	bool eraseHelper(DictionaryNode* root, const char* word);
};
