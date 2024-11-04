#include <filesystem>
#include "../src/Interface.h"

namespace fs = std::filesystem;

/// Display how to use the program from the command line
void displayUsage(const char* executablePath)
{
  try {
    fs::path ep(executablePath);
    
    std::cout
      << "Usage:\n\t"
      << ep.filename()
      << " <dictionary> <filter> <text>"
      << std::endl;
  }
  catch (...) {
    std::cout << "Cannot parse path from argv[0]";
  }
}

int main(int argc, char* argv[])
{
    argv[4];
    argc = 4;

    if(argc < 4) {
    displayUsage(argv[0]);
    return 1;
    }

    //TODO implement the program

    Dictionary dictionaryTrie;

    Statistics dictionaryStats;
    std::cout << "Loading dictionary from .\\input-sample\\";
    loadFile(dictionaryTrie, File::Dictionary, dictionaryStats);

    Statistics filterStats;
    std::cout << "Removing the words listed at .\\input-sample\\";
    loadFile(dictionaryTrie, File::Filter, filterStats);

    Statistics verifyStats;
    std::cout << "Verifying the contents of .\\input-sample\\";
    verify(dictionaryTrie, File::VerifyText, verifyStats);

    std::cout << std::endl;
    std::cout << "Statistics: " << std::endl;
    std::cout << "  Dictionary entries: ";
    dictionaryStats.print();

    std::cout << "      Filter entries: ";
    filterStats.print();

    std::cout << " Resultat dictionary: " << dictionaryTrie.size() << std::endl;

    std::cout << "       Words in text: ";
    verifyStats.print();

    return 0;
}