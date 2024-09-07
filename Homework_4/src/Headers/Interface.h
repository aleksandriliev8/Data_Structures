#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "../src/Definitions.h"
#include "../src/Dictionary.h"
#include "../src/Statistics.h"
#include "../src/File.h"
#include "../src/HelperFunctions.h"

void loadFile(Dictionary& dictionaryTrie, const File& fileInfo, Statistics& stats) {

    std::string line;
    std::string filePath;
    // dictionary.txt or text.txt
    std::cin >> filePath;

    filePath = allPath + filePath;

    std::ifstream sourceFile(filePath);

    if (!sourceFile.is_open()) {
        std::cerr << "Couldn't open the file ." << std::endl;
        return;
    }

    unsigned int lineCounter = 0;

    while (std::getline(sourceFile, line)) {
        if (!line.empty() && line[0] == '#' || hasNoSybols(line)) {
            continue;
        }

        const char* word = line.c_str();
        lineCounter++;

        if (Dictionary::isCorrectWord(word)) {

            if (fileInfo == File::Dictionary) {
                dictionaryTrie.insert(word);
            }

            else if (fileInfo == File::Filter) {
                dictionaryTrie.erase(word);
            }

            stats.increaseCorrect();
        }

        else {
            std::cout << "ERROR: incorrect entry \"" << word << "\" on line " << lineCounter << std::endl;
            stats.increaseIncorrect();
        }

    }

    sourceFile.close();

    std::cout << std::endl;
}

void verify(Dictionary& dictionaryTrie, const File& fileInfo, Statistics& stats) {

    std::string filePath;
    // text.txt
    std::cin >> filePath;

    filePath = allPath + filePath;

    std::ifstream sourceFile(filePath);

    if (!sourceFile.is_open()) {
        std::cerr << "Couldn't open the file ." << std::endl;
        return;
    }

    unsigned int lineCounter = 1;

    std::string line;
    while (std::getline(sourceFile, line)) {
        std::istringstream lineStream(line);
        std::string word;

        while (lineStream >> word) {

            const char* lineWord = word.c_str();

            if (dictionaryTrie.contains(lineWord)) {
                stats.increaseCorrect();
            }
            else {
                stats.increaseIncorrect();
                std::cout << "SPELLING ERROR: \"" << lineWord << "\" on line " << lineCounter << std::endl;
            }
        }

        ++lineCounter;
    }

    sourceFile.close();
}