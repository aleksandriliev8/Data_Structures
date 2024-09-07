#include "Dictionary.h"
#include <cctype> // Contains std::isalpha()

//TODO Implement the Dictionary class

void Dictionary::clear(DictionaryNode* node) {
	if (!node) return;
	for (size_t i = 0; i < alphabetSize; ++i)
	{
		if (node->children[i]) {
			clear(node->children[i]);
		}
	}

	delete node;
}

void Dictionary::insert(const char* word)
{	
	if (word == nullptr || !*word) {
		throw incorrect_word_exception();
	}
		
    DictionaryNode* currNode = root;

    while (*word) {
		int index = 0;

		if (*word >= 'A' && *word <= 'Z') {
			index = *word - 'A';
		}
		else if (*word >= 'a' && *word <= 'z') {
			index = *word - 'a';
		}
		else {
			throw incorrect_word_exception();
			return;
		}

        if (currNode->children[index] == nullptr) {
            currNode->children[index] = new DictionaryNode();
			currNode->value = *word;
        }
        currNode = currNode->children[index];
        word++;
    }
    currNode->isEndOfWord = true;

	sizeDictionary++;
}

bool Dictionary::isEmpty(DictionaryNode* root) {
	for (size_t i = 0; i < alphabetSize; i++)
	{
		if (root->children[i]) {
			return false;
		}
		return true;
	}
}

bool Dictionary::eraseHelper(DictionaryNode* node, const char* word) {
	if (*word == '\0') {
		if (!node->isEndOfWord) {
			return false;
		}
		node->isEndOfWord = false;
		sizeDictionary--;
		return isEmpty(node);
	}

	int index = *word - 'a';

	if (eraseHelper(node->children[index], word + 1)) {
		delete node->children[index];
		node->children[index] = nullptr;
		return !node->isEndOfWord && isEmpty(node);
	}

	return false;
}


void Dictionary::erase(const char* word) noexcept
{
	if (!root || !isCorrectWord(word) || !contains(word)) {
		return;
	}

	eraseHelper(root, word);
}

bool Dictionary::contains(const char* word) const noexcept
{
	if (word == nullptr) return false;

	DictionaryNode* currNode = root;

	while (*word) {
		int index = *word - 'a';

		//if the symbol doesn't exist, the word dosen't too
		if (!currNode->children[index]) {
			return false;
		}

		currNode = currNode->children[index];
		word++;
	}

	return currNode->isEndOfWord;
}

size_t Dictionary::size() const noexcept
{
	return sizeDictionary;
}

bool Dictionary::isCorrectWord(const char* word) noexcept
{
	if (!word)
		return false;
	else if (!*word)
		return false;

	while (*word) {
		if (*word < 'A' || (*word > 'Z' && *word < 'a') || *word > 'z')
			return false;

		word++;
	}

	return true;
}
